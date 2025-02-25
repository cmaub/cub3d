/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:59:12 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/25 12:23:53 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_to_map(char **str, int *i, t_map *map)
{
	while (str[*i] && (!str[*i][0] || ft_is_only_spaces(str[*i])))
		(*i)++;
	str += *i;
	if (!str)
		return (printf("Error\nmissing map\n"), FALSE);
	if (!check_map(str, map, *i))
		return (FALSE);
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
		while (!str[i][0] || ft_is_only_spaces(str[i]))
		{
			if (temp_all_path_filled(map))
				break ;
			i++;
		}
		if (!fill_texture_path(str[i], map) || !fill_color(str[i], map))
			return (FALSE);
		if (other_information(str[i][0]))
			break ;
		i++;
	}
	if (!final_all_path_filled(map))
		return (FALSE);
	if (!move_to_map(str, &i, map))
		return (FALSE);
	return (TRUE);
}

void	fill_and_check_file(t_params *par)
{
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	while (1)
	{
		str = get_next_line(par->fd);
		if (!str)
			break ;
		if (str[ft_strlen(str) - 1] == '\n')
			str[ft_strlen(str) - 1] = '\0';
		par->map->parse_file[i] = clean_malloc(sizeof(char)
				* par->map->length_max + 1, par);
		ft_strlcpy(par->map->parse_file[i], str, par->map->length_max);
		free(str);
		i++;
	}
	close(par->fd);
	par->fd = -1;
	par->map->parse_file[i] = ft_strdup("");
	if (!par->map->parse_file[i])
		close_window(par);
	if (!check_av(par->map, par->map->parse_file))
		close_window(par);
}

void	ft_hook(t_params *par)
{
	mlx_hook(par->win_ptr, 17, 0, close_window, par);
	mlx_hook(par->win_ptr, 2, 1L << 0, key_press, par);
	mlx_hook(par->win_ptr, 3, 1L << 1, key_release, par);
	mlx_loop_hook(par->mlx_ptr, key_update, par);
}

int	main(int ac, char **av, char **envp)
{
	t_params	*par;

	if (ac != 2)
		return (printf("Error\nwrong number of argument\n"), 1);
	if (!envp || !*envp)
		return (printf("Error\nthe program cannot run with no environment\n"), 1);
	if (!check_ext(av[1], ".cub"))
		return (1);
	par = clean_malloc(sizeof(t_params), NULL);
	init_t_map(par);
	if (!count_alloc(par->map, av[1]))
		return (close_window(par), 1);
	par->fd = open(av[1], R_OK);
	if (par->fd == -1)
		return (printf("Error\nthe file cannot be open"), close_window(par), 1);
	fill_and_check_file(par);
	init_structs(par);
	draw_floor(par, par->map);
	wall_casting(par, par->player, par->map);
	ft_hook(par);
	mlx_loop(par->mlx_ptr);
	free(par);
	return (0);
}
