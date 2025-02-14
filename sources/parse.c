/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:31:48 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/14 10:37:17 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	all_path_filled(t_map *map)
{
	if (!map->path_no || !map->path_so || !map->path_ea || !map->path_we || map->rgb_floor == -1|| map->rgb_ceil == -1)
		return (FALSE);
	return (TRUE);
}

int	check_map(char **str, t_map *map, int index)
{
	int	i;
	int	j;
	int	len_i;
	int	count_j;
	int	flag;
	int save_index;
	
	i = 0;
	len_i = 0;
	count_j = 0;
	flag = 0;
	save_index = index;
	map->length_max = 0;
	while (str[i] && index < map->nb_lines)
	{
		// printf("str[%d] = %s\n", i, str[i]);
		j = 0;
		len_i = ft_strlen(str[i]);
		if (len_i > map->length_max)
			map->length_max = len_i;
		while (str[i][j] && j < len_i)
		{
			if (i == 0 || j == 0 || j == len_i - 1|| !str[i + 1])
			{
				if ((str[i][j] !=  '1' && str[i][j] != ' '))
				{
					printf("error line %d\n", __LINE__); //TODO
					return (FALSE);
				}
				if (str[i][j] == ' ')
				{
					if (j != 0)
					{
						if (str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
					if (j != len_i)
					{
						if (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
					if (i != 0)
					{
						if (str[i - 1][j] && !ft_strchr("1 ", str[i - 1][j]))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
					if (str[i + 1])
					{
						if (str[i + 1][j] && !ft_strchr("1 ", str[i + 1][j]))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
				}
			}
			else 
			{
				if (!ft_strchr("01NEWS ", str[i][j]))
				{
					printf("error line %d\n", __LINE__); //TODO
					return (FALSE);
				}
				if (str[i][j] == ' ')
				{
					if (j < (int)ft_strlen(str[i - 1]))
					{	
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
							|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
							|| (str[i - 1][j] && !ft_strchr("1 ", str[i - 1][j])))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
					else
					{
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1])))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
					if (j < (int)ft_strlen(str[i + 1]))
					{	
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
							|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
							|| (str[i + 1][j] && !ft_strchr("1 ", str[i + 1][j])))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
					else
					{
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1])))
						{
							printf("error line %d\n", __LINE__); //TODO
							return (FALSE);
						}
					}
				}
				if (ft_strchr("NEWS", str[i][j]))
				{
					init_player_angle(map->player, str[i][j], i, j);
					flag++;
				}
			}
			j++;
		}
		if (index <  map->nb_lines && j == 0)
		{
			printf("error, ligne vide\n");
			return (FALSE);
		}
		i++;
		index += 1;
	}
	map->nb_lines = i;
	map->unit_v_mini = HEIGHT_MINI / map->nb_lines;
	map->unit_h_mini = WIDTH_MINI / map->length_max;
	if (flag != 1)
	{
		printf("error line %d\n", __LINE__); //TODO
		return (FALSE);
	}
	printf("******* map->player->plane_x = %f, map->player->dir_x = %f\n", map->player->plane_x, map->player->dir_x);
	replace_spaces(str, map);
	map->map_tab = str;
	// print_map(str);
	return (TRUE);
}

int	check_av(t_map *map, char **str, int count)
{
	int	i;
	(void)count;

	i = 0;
	
	while (str[i] && !str[i][0])
	{
		i++;
	}
	while (str[i] && i < count)
	{
		if (!str[i][0])
		{
			if (all_path_filled(map))
				break;
			i++;
		}
		if (!ft_strncmp(str[i], "NO", 2))
		{
			if (map->path_no)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_no = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "SO", 2))
		{
			if (map->path_so)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_so = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "WE", 2))
		{
			if (map->path_we)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_we = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "EA", 2))
		{
			if (map->path_ea)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_ea = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "F ", 2))
		{
			if (map->rgb_floor != -1)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			if (!check_color_params(str[i], &map->rgb_floor))
				return (printf("error\n"), FALSE); //TODO
			
		}
		if (!ft_strncmp(str[i], "C ", 2))
		{
			if (map->rgb_ceil != -1)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			if (!check_color_params(str[i], &map->rgb_ceil))
				return (printf("error\n"), FALSE);
		}
		i++;
	}
	if (!all_path_filled(map))
	{
		//free
		printf("error line %d\n", __LINE__);
		return (FALSE);
	}
	while (!str[i][0])
			i++;
	str += i;
	check_map(str, map, i);
	
	return (TRUE);
}

