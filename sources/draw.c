/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:33:25 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/04 17:52:12 by anvander         ###   ########.fr       */
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
	while (j < map->length_max)
	{
		if (x % (WIDTH / map->length_max) == 0)
		{
			y = 0;
			while (y <= HEIGHT)
			{
				my_mlx_pixel_put(img, x, y, rgb_to_int(255, 255, 255));
				y++;
			}
		}
		j++;
		x += WIDTH / map->length_max;
	}
	if (j == map->length_max)
	{
		y = 0;
		while (y <= HEIGHT)
		{
			my_mlx_pixel_put(img, x - 1, y - 1, rgb_to_int(255, 255, 255));
			y++;
		}
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
	while (i < map->nb_lines)
	{
		if (y % (HEIGHT / map->nb_lines) == 0)
		{
			x = 0;
			while (x <= WIDTH)
			{
				my_mlx_pixel_put(img, x, y, rgb_to_int(255, 255, 255));
				x++;
			}
		}
		i++;
		y += HEIGHT / map->nb_lines;
	}
	if (i == map->nb_lines)
	{
		x = 0;
		while (x <= WIDTH)
		{
			my_mlx_pixel_put(img, x - 1, y - 1, rgb_to_int(255, 255, 255));
			x++;
		}
	}
}

void	draw_player(t_img *img, t_map *map, t_player *player, double x, double y)
{
	int	y_p;
	int	x_p;
	int	unit_h;
	int	unit_v;

	unit_h = WIDTH / map->length_max;
	unit_v = HEIGHT / map->nb_lines;
	x_p = x + unit_h / 2;
	y_p = y + unit_v / 2;
	my_mlx_pixel_put(img, x_p,  y_p, player->color);
}

void    draw_map(t_img *img, t_map *map)
{
    int	j;
	int	i;
	int	unit_v;
	int	unit_h;
	double	x;
	double	y;
	double	saved_x;
	double	saved_y;
	
	i = 0;
	y = 0.0;
	x = 0.0;
	unit_h = WIDTH / map->length_max;
	unit_v = HEIGHT / map->nb_lines;
	saved_x = x;
	saved_y = y;
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
	while (i < map->nb_lines)
	{
		j = 0;
		x = 0;
		while (j < map->length_max)
		{
			if (map->map_tab[i][j] && map->map_tab[i][j] == '1')
			{
				y = saved_y;
				while (y <= saved_y + unit_v)
				{
					x = saved_x;
					while (x < saved_x + unit_h)
					{
						my_mlx_pixel_put(img, x, y, rgb_to_int(128, 128, 128));
						x++;
					}
					y++;
				}
			}
			if (map->map_tab[i][j] && ft_strchr("NEWS", map->map_tab[i][j]))
			{
				img->player->pos_y = saved_y;
				img->player->pos_x = saved_x;			
			}
			j++;
			x = j * unit_h;
			saved_x = x;
			if (saved_x + unit_h > WIDTH)
				saved_x = 0;

		}
		i++;
		y = i * unit_v;
		saved_y = y;
	}
}

