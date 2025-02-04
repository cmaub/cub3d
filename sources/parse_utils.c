/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:34:35 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/04 14:18:47 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_tab(char **str, t_map *map)
{
	int	i;

	printf("map->path_no = %s\n", map->path_no);
	printf("map->path_so = %s\n", map->path_so);
	printf("map->path_we = %s\n", map->path_we);
	printf("map->path_ea = %s\n", map->path_ea);
	printf("map->rgb_floor = %d\n", map->rgb_floor);
	printf("map->rgb_ceil = %d\n", map->rgb_ceil);
	i = 0;
	while (str[i])
	{
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
}

void	print_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("map[%d] = %s\n", i, str[i]);
		i++;
	}
}

void	replace_spaces(char **str, t_map *map, int index)
{
	int	i;
	int	j;
	(void)index;

	i = 0;
	// map->map_tab = try_malloc(sizeof(char *))
	while (str[i] && i < map->nb_lines)
	{
		j = 0;
		while (str[i][j] && j < map->length_max)
		{
			if (str[i][j] == ' ')
				str[i][j] = '1';
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
