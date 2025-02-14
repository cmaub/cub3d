/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:59:12 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/14 11:07:25 by anvander         ###   ########.fr       */
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
void	color_image(t_params *par)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(par->mini_map, x, y, 255);
			// my_mlx_pixel_put(par->mini_map, x, y, 0);
			x++;
		}
		y++;
	}
}

int main(int ac, char **av)
{
    t_params *par;
	int	fd;
	char	*str;
	int	i;
	(void)ac;

	par = try_malloc(sizeof(t_params));
	
	init_t_map(par);
	// revoir verification exit
	count_alloc(par->map, av[1]);
	fd = open(av[1], R_OK);
	i = 0;
	str = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if(str[ft_strlen(str) -1] == '\n')
			str[ft_strlen(str) -1] = '\0';
		par->map->parse_file[i] = try_malloc(sizeof(char) * par->map->length_max + 1);
		ft_strlcpy(par->map->parse_file[i], str, par->map->length_max);
		free(str);
		i++;
	}
	par->map->parse_file[i] = "\0";
	if (!check_av(par->map, par->map->parse_file, i))
		return (1);
	// print_tab(par->map->map_tab, par->map);
    init_structs(par);
	build_mini_map(par->mini_map, par->map, par);
	dprintf(2, "line %d, file %s, par->player->pos_x = %f\n", __LINE__, __FILE__, par->player->pos_x);
	draw_vertical_grid(par->mini_map, par->map);
	draw_horizontal_grid(par->mini_map, par->map);
	// dprintf(2, "line %d, file %s\n", __LINE__, __FILE__);
	draw_fov(par, par->mini_map, par->map, par->player, 255);
	// floor_casting(par, par->player, par->map);
	dprintf(2, "line %d, file %s, par->player->pos_x = %f\n", __LINE__, __FILE__, par->player->pos_x);
	wall_casting(par, par->player, par->map);
	// dprintf(2, "line %d, file %s\n", __LINE__, __FILE__);
	// mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
	// draw_3d(par, par->img, par->map, par->player, 255);
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
	mlx_key_hook(par->win_ptr, key_event, par);
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
    mlx_loop(par->mlx_ptr);
	free(par);
    return (0);
}
