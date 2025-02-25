/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:31:48 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/25 12:14:23 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_north(char *str, char **tab, t_map *map)
{
	if (!ft_strncmp(str, "NO ", 3))
	{
		if (map->path_no)
			return (printf("Error\ntoo many path for North texture\n"),
				free_tab(tab), FALSE);
		map->path_no = ft_strdup(tab[1]);
		if (!map->path_no)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
	return (TRUE);
}

int	check_south(char *str, char **tab, t_map *map)
{
	if (!ft_strncmp(str, "SO ", 3))
	{
		if (map->path_so)
			return (printf("Error\ntoo many path for South texture\n"),
				free_tab(tab), FALSE);
		map->path_so = ft_strdup(tab[1]);
		if (!map->path_so)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
	return (TRUE);
}

int	check_west(char *str, char **tab, t_map *map)
{
	if (!ft_strncmp(str, "WE ", 3))
	{
		if (map->path_we)
			return (printf("Error\ntoo many path for West texture\n"),
				free_tab(tab), FALSE);
		map->path_we = ft_strdup(tab[1]);
		if (!map->path_we)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
	return (TRUE);
}

int	check_east(char *str, char **tab, t_map *map)
{
	if (!ft_strncmp(str, "EA ", 3))
	{
		if (map->path_ea)
			return (printf("Error\ntoo many path for East texture\n"),
				free_tab(tab), FALSE);
		map->path_ea = ft_strdup(tab[1]);
		if (!map->path_ea)
			return (free_tab(tab), printf("Error\nerror of allocation\n"), FALSE);
	}
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
	if (!check_north(str, tab, map))
		return (FALSE);
	if (!check_south(str, tab, map))
		return (FALSE);
	if (!check_west(str, tab, map))
		return (FALSE);
	if (!check_east(str, tab, map))
		return (FALSE);
	return (free_tab(tab), TRUE);
}
