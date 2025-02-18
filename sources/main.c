/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:59:12 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/18 15:33:23 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy(t_params *par)
{
	if (par->img->img)
		mlx_destroy_image(par->mlx_ptr, par->img->img);
	if (par->win_ptr)
		mlx_destroy_window(par->mlx_ptr, par->win_ptr);
	if (par->mlx_ptr)
	{
		mlx_destroy_display(par->mlx_ptr);
		free(par->mlx_ptr);
	}
	// if (par)
	// 	free_params(par);
	exit(0);
}

int main(int ac, char **av)
{
    t_params *par;
	char	*str;
	int	i;
	(void)ac;

	if (ac != 2)
		return (1);
	if (!check_extension(av[1], ".cub"))
		return (1);
	par = clean_malloc(sizeof(t_params), NULL);
	init_t_map(par);
	if (!count_alloc(par->map, av[1]))
		return (close_window(par), 1);
	par->fd = open(av[1], R_OK);
	if (par->fd == -1)
		return (close_window(par), 1);
	i = 0;
	str = NULL;
	while (1)
	{
		str = get_next_line(par->fd);
		if (!str)
			break ;
		if(str[ft_strlen(str) -1] == '\n')
			str[ft_strlen(str) -1] = '\0';
		par->map->parse_file[i] = clean_malloc(sizeof(char) * par->map->length_max + 1, par);
		ft_strlcpy(par->map->parse_file[i], str, par->map->length_max);
		free(str);
		i++;
	}
	close(par->fd);
	par->fd = -1;
	par->map->parse_file[i] = ft_strdup("");
	if (!par->map->parse_file[i])
		close_window(par);
	if (!check_av(par->map, par->map->parse_file, i))
		return (close_window(par), 1);
    init_structs(par);
	// build_mini_map(par->mini_map, par->map, par);
	// draw_vertical_grid(par->mini_map, par->map);
	// draw_horizontal_grid(par->mini_map, par->map);
	// draw_fov(par, par->mini_map, par->map, par->player, 255);
	floor_casting(par, par->map);
	wall_casting(par, par->player, par->map);
	// mlx_key_hook(par->win_ptr, key_event, par);
	mlx_hook(par->win_ptr, 17, 0, close_window, par);
	mlx_hook(par->win_ptr, 2, 1L << 0, key_press, par);
	mlx_hook(par->win_ptr, 3, 1L << 1, key_release, par);
	mlx_loop_hook(par->mlx_ptr, key_update, par);
    mlx_loop(par->mlx_ptr);
	free(par);
    return (0);
}
