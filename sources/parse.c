/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:31:48 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/19 17:04:34 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *map, char *ext)
{
	char *str;
	int	len;

	len = 0;
	len = ft_strlen(map);
	str = map;
	str += len - 4;
	
	if (ft_strncmp(str, ext, 4) != 0)
		return (FALSE);
	return (TRUE);
}

int	all_path_filled(t_map *map)
{
	int	fd;
	
	if (!map->path_no || !map->path_so || !map->path_ea || !map->path_we 
		|| map->rgb_floor == -1 || map->rgb_ceil == -1)
		return (FALSE);
	fd = open(map->path_no, R_OK);
	if (fd == -1)
		return (FALSE);
	close(fd);
	fd = open(map->path_so, R_OK);
	if (fd == -1)
		return (FALSE);
	close(fd);
	fd = open(map->path_ea, R_OK);
	if (fd == -1)
		return (FALSE);
	close(fd);
	fd = open(map->path_we, R_OK);
	if (fd == -1)
		return (FALSE);
	close(fd);
	if (!check_extension(map->path_no, ".xpm") || !check_extension(map->path_so, ".xpm") 
		|| !check_extension(map->path_ea, ".xpm") || !check_extension(map->path_we, ".xpm"))
		return (FALSE);
	return (TRUE);
}

int	check_line(char **str, int i, int*j, t_map *map)
{
	while (str[i][*j] && *j < (int)ft_strlen(str[i]))
	{
		if (i == 0 || *j == 0 || *j == (int)ft_strlen(str[i]) -1 || !str[i + 1][0] )
		{
			if ( str[i][*j] != '1')
				return (FALSE);
		}
		if (str[i][*j] == ' ' || str[i][*j] == '0')
		{
			if (str[i + 1][*j] == '\0' || str[i + 1][*j] == '\n')
				return (printf("0 ou espace non protege ligne %d\n", i), FALSE);
		}
		else
		{
			if (!ft_strchr("01 NEWS", str[i][*j]))
				return (FALSE);
			if (ft_strchr("NEWS", str[i][*j]))
			{
				init_player_angle(map->player, str[i][*j], i, *j);
				map->flag++;
			}
		}
		(*j)++;
	}
	return (TRUE);
}

int	check_map(char **str, t_map *map, int idx)
{
	int	i;
	int	j;

	i = 0;
	map->flag = 0;
	map->length_max = 0;
	while (str[i] && idx < map->nb_lines)
	{
		j = 0;
		if ((int)ft_strlen(str[i]) > map->length_max)
			map->length_max = ft_strlen(str[i]);
		if (!check_line(str, i, &j, map) || (idx < map->nb_lines && j == 0))
			return (FALSE);
		i++;
		idx += 1;
	}
	dprintf(2, "i = %d\n", i);
	map->nb_lines = i;
	map->unit_v_mini = (double)(HEIGHT_MINI / map->nb_lines);
	dprintf(2, "map->unit_v_mini = %f\n", map->unit_v_mini);
	map->unit_h_mini = (double)(WIDTH_MINI / map->length_max);
	dprintf(2, "map->length_max = %d, map->unit_h_mini = %f\n", map->length_max, map->unit_h_mini);
	if (map->flag != 1)
		return (FALSE);
	replace_spaces(str, map);
	map->map_tab = str;
	return (TRUE);		
}

int	fill_texture_path(char *str, t_map *map)
{
	if (!ft_strncmp(str, "NO", 2))
	{
		if (map->path_no)
			return (printf("too many path for north texture\n"), FALSE);
		map->path_no = ft_substr(str, 3, ft_strlen(str) - 3);
	}
	if (!ft_strncmp(str, "SO", 2))
	{
		if (map->path_so)
			return (printf("too many path for south texture\n"), FALSE);
		map->path_so = ft_substr(str, 3, ft_strlen(str) - 3);
	}
	if (!ft_strncmp(str, "WE", 2))
	{
		if (map->path_we)
			return (printf("too many path for west texture\n"), FALSE);
		map->path_we = ft_substr(str, 3, ft_strlen(str) - 3);
	}
	if (!ft_strncmp(str, "EA", 2))
	{
		if (map->path_ea)
			return (printf("too many path for east texture\n"), FALSE);
		map->path_ea = ft_substr(str, 3, ft_strlen(str) - 3);
	}
	return (TRUE);
}

int	fill_color(char *str, t_map *map)
{
	if (!ft_strncmp(str, "F ", 2))
	{
		if (map->rgb_floor != -1)
			return (printf("choose only one color for floor\n"), FALSE);
		if (!check_color_params(str, &map->rgb_floor))
			return (printf("invalid color\n"), FALSE);
		
	}
	if (!ft_strncmp(str, "C ", 2))
	{
		if (map->rgb_ceil != -1)
			return (printf("choose only one color for ceilling\n"), FALSE);
		if (!check_color_params(str, &map->rgb_ceil))
			return (printf("invalid color\n"), FALSE);
	}
	return (TRUE);
}

int	check_av(t_map *map, char **str)
{
	int	i;

	i = 0;
	while (str[i] && !str[i][0])
		i++;
	while (str[i])
	{
		if (!str[i][0])
		{
			if (all_path_filled(map))
				break;
			i++;
		}
		if (!fill_texture_path(str[i], map) || !fill_color(str[i], map))
			return (FALSE);
		i++;
	}
	if (!all_path_filled(map))
		return (printf("invalid path\n"), FALSE);
	while (!str[i][0])
			i++;
	str += i;
	if (!check_map(str, map, i))
		return (printf("invalid map\n"), FALSE);
	return (TRUE);
}

