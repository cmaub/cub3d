/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:33:25 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/13 17:58:25 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->l_len + x * (img->b_pix / 8));
	*(unsigned int *)dst = color;
}

void	clear_image(t_params *par)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// my_mlx_pixel_put(par->img, x, y, 0);
			my_mlx_pixel_put(par->img, x, y, 0);
			x++;
		}
		y++;
	}
}

void	draw_vertical_grid(t_img *img, t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (j <= map->length_max)
	{
		if (x % map->unit_h_mini == 0)
		{
			y = 0;
			while (y <= HEIGHT_MINI)
			{
				my_mlx_pixel_put(img, x, y, rgb_to_int(255, 255, 255));
				y++;
			}
		}
		j++;
		x += map->unit_h_mini;
	}
}

void	draw_horizontal_grid(t_img *img, t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (i <= map->nb_lines)
	{
		if (y % map->unit_v_mini == 0)
		{
			x = 0;
			while (x <= WIDTH_MINI)
			{
				my_mlx_pixel_put(img, x, y, rgb_to_int(255, 255, 255));
				x++;
			}
		}
		i++;
		y += map->unit_v_mini;
	}
}

void	draw_player(t_img *img, double x, double y, int color)
{
	int	i;
	int	j;
	
	i = -3;
	j = -3;
	while (i < 4)
	{
		j = -3;
		while (j < 4)
		{
			my_mlx_pixel_put(img, x - i,  y - j, color);
			j++;
		}
		i++;
	}
}

void	init_player_vars(t_map *map, t_player **player, double x, double y)
{
	// (*player)->pos_x = x + map->unit_h_mini / 2;
	// (*player)->pos_y = y + map->unit_v_mini / 2;
	// // (*player)->pos_x = x;
	// // (*player)->pos_y = y;
	// (*player)->p_size = map->unit_v_mini / 2;
	// (*player)->dist_to_p = map->unit_h_mini / 2 / tan(FOV / 2);
	(*player)->pos_x = x * (double)map->unit_h_mini + (double)map->unit_h_mini / 2;
	(*player)->pos_y = y * (double)map->unit_v_mini + (double)map->unit_v_mini / 2;
	(*player)->p_size = map->unit_v_mini / 2;
	(*player)->dist_to_p = map->unit_h_mini / 2 / tan(FOV / 2);
	dprintf(2, "**** player pos_x = %f, pos_y = %f\n", (*player)->pos_x, (*player)->pos_y);

}

void	draw_walls(t_img *img, t_map *map, double *x, double *y, double saved_x, double saved_y)
{
	*y = saved_y;
	while (*y <= saved_y + map->unit_v_mini)
	{
		*x = saved_x;
		while (*x < saved_x + map->unit_h_mini)
		{
			my_mlx_pixel_put(img, *x, *y, rgb_to_int(128, 128, 128));
			(*x)++;
		}
		(*y)++;
	}
}

void	draw_first_map(t_img *mini_map, t_map *map, t_player *player, int i, double y, double saved_y)
{
	int		j;
	double	x;
	double	x_p;
	double	x_y;
	double	saved_x;
	(void)y;
	
	j = 0;
	x = 0.0;
	saved_x = x;
	x_p = 0;
	x_y = 0;
	
	while (j < map->length_max)
	{
		if (map->map_tab[i][j] && map->map_tab[i][j] == '1')
			draw_walls(mini_map, map, &x, &y, saved_x, saved_y);
		if (map->map_tab[i][j] && ft_strchr("NEWS", map->map_tab[i][j]))
		{
			x_p = saved_x + map->unit_h / 2; //
			x_y = saved_y + map->unit_v / 2;
			draw_player(mini_map, x_p, x_y, rgb_to_int(255, 0, 0));
			dprintf(2, "i %d, j %d, x_p %f, x_y %f, saved_x %f, saved_y %f\n", i, j, x_p, x_y, saved_x, saved_y);
			init_player_vars(map, &player, j, i);
		}
		j++;
		x = j * map->unit_h_mini;
		saved_x = x;
		if (saved_x + map->unit_h_mini > WIDTH_MINI)
			saved_x = 0;
	}
}

void    build_mini_map(t_img *mini_map, t_map *map, t_params *par)
{
	int	i;
	double	y;
	double	saved_y;
	
	y = 0.0;
	i = 0;
	saved_y = y;
	while (i < map->nb_lines)
	{
		draw_first_map(mini_map, map, par->player, i, y, saved_y);
		i++;
		y = i * map->unit_v_mini;
		saved_y = y;
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, mini_map->img, WIDTH - WIDTH_MINI, HEIGHT - HEIGHT_MINI);
}
