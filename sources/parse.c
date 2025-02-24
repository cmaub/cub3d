/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:31:48 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/24 17:59:15 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(char **str, int i, int*j, t_map *map)
{
	while (str[i][*j] && *j < (int)ft_strlen(str[i]))
	{
		if ((i == 0 || *j == 0 || *j == (int)ft_strlen(str[i]) - 1
				|| !str[i + 1][0]) && str[i][*j] != '1')
		{
			if (!ft_strchr("01 ", str[i][0]))
				return (printf("Error\nthe map is filled with wrong char\n"),
			FALSE);
			return (printf("Error\nthe map is unclosed\n"), FALSE);
		}
		if (str[i][*j] == ' ' || str[i][*j] == '0')
		{
			if (str[i + 1][*j] == '\0' || str[i + 1][*j] == '\n')
				return (printf("Error\nthe map is unclosed\n"), FALSE);
			if (str[i - 1][*j] == '\0' || str[i - 1][*j] == '\n')
				return (printf("Error\nthe map is unclosed\n"), FALSE);
		}
		else
		{
			if (!ft_strchr("01 NEWS", str[i][*j]))
				return (printf("Error\nthe map is filled with wrong char\n"),
					FALSE);
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

	i = -1;
	map->flag = 0;
	map->length_max = 0;
	while (str[++i] && idx < map->nb_lines)
	{
		j = 0;
		if ((int)ft_strlen(str[i]) > map->length_max)
			map->length_max = ft_strlen(str[i]);
		if (!check_line(str, i, &j, map))
			return (FALSE);
		if ((idx < map->nb_lines && j == 0))
			return (printf("Error\nempty line in map definition\n"), FALSE);
		idx += 1;
	}
	map->nb_lines = i;
	map->v_mini = (double)(HEIGHT / map->nb_lines) / 5.0;
	map->h_mini = (double)(WIDTH / map->length_max) / 5.0;
	if (map->flag != 1)
		return (printf("Error\ncannot find player position\n"), FALSE);
	replace_spaces(str, map);
	map->map_tab = str;
	return (TRUE);
}

int	fill_texture_path(char *str, t_map *map)
{
	char	**tab;

	if (!str[0] || ft_is_only_spaces(str))
		return (TRUE);
	tab = ft_split(str, ' ');
	if (!tab)
		return (FALSE);
	if (!ft_strncmp(str, "NO ", 3))
	{
		if (map->path_no)
			return (printf("Error\ntoo many path for north texture\n"), free_tab(tab), FALSE);
		map->path_no = ft_strdup(tab[1]);
		if (!map->path_no)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
	if (!ft_strncmp(str, "SO ", 3))
	{
		if (map->path_so)
			return (printf("Error\ntoo many path for south texture\n"), free_tab(tab), FALSE);
		map->path_so = ft_strdup(tab[1]);
		if (!map->path_so)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
	if (!ft_strncmp(str, "WE ", 3))
	{
		if (map->path_we)
			return (printf("Error\ntoo many path for west texture\n"), free_tab(tab), FALSE);
		map->path_we = ft_strdup(tab[1]);
		if (!map->path_we)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
	if (!ft_strncmp(str, "EA ", 3))
	{
		if (map->path_ea)
			return (printf("Error\ntoo many path for east texture\n"), free_tab(tab), FALSE);
		map->path_ea = ft_strdup(tab[1]);
		if (!map->path_ea)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
	return (free_tab(tab), TRUE);
}

int	fill_color(char *str, t_map *map)
{
	char	**tab;

	if (!str[0] || ft_is_only_spaces(str))
		return (TRUE);
	tab = ft_split(str, ' ');
	if (!tab)
		return (FALSE);
	if (!ft_strncmp(str, "F ", 2))
	{
		if (map->rgb_floor != -1)
			return (printf("Error\nchoose only one color for floor\n"), FALSE);
		if (!check_color_params(tab[1], &map->rgb_floor))
			return (printf("Error\ninvalid color\n"), free_tab(tab), FALSE);
	}
	if (!ft_strncmp(str, "C ", 2))
	{
		if (map->rgb_ceil != -1)
			return (printf("Error\nchoose only one color for ceilling\n"), FALSE);
		if (!check_color_params(tab[1], &map->rgb_ceil))
			return (printf("Error\ninvalid color\n"), free_tab(tab), FALSE);
	}
	return (free_tab(tab), TRUE);
}
