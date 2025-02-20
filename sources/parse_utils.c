/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:34:35 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/20 14:28:16 by anvander         ###   ########.fr       */
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
		return (printf("Error\ncheck extension file\n"), FALSE);
	return (TRUE);
}

void	replace_spaces(char **str, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && i < map->nb_lines)
	{
		j = 0;
		while (str[i][j] && j < map->length_max)
		{
			if (str[i][j] == ' ')
				str[i][j] = '0';
			j++;
		}
		while (j < map->length_max)
		{
			if (str[i][j] == '\0')
				str[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	temp_all_path_filled(t_map *map)
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

int	final_all_path_filled(t_map *map)
{
	int	fd;

	if (!map->path_no || !map->path_so || !map->path_ea || !map->path_we 
		|| map->rgb_floor == -1 || map->rgb_ceil == -1)
		return (printf("Error\nmissing param for map definition"), FALSE);
	fd = open(map->path_no, R_OK);
	if (fd == -1)
		return (printf("Error\ncannot open %s\n", map->path_no), FALSE);
	close(fd);
	fd = open(map->path_so, R_OK);
	if (fd == -1)
		return (printf("Error\ncannot open %s\n", map->path_so), FALSE);
	close(fd);
	fd = open(map->path_ea, R_OK);
	if (fd == -1)
		return (printf("Error\ncannot open %s\n", map->path_ea), FALSE);
	close(fd);
	fd = open(map->path_we, R_OK);
	if (fd == -1)
		return (printf("Error\ncannot open %s\n", map->path_we), FALSE);
	close(fd);
	if (!check_extension(map->path_no, ".xpm") || !check_extension(map->path_so, ".xpm") 
		|| !check_extension(map->path_ea, ".xpm") || !check_extension(map->path_we, ".xpm"))
		return (FALSE);
	return (TRUE);
}
