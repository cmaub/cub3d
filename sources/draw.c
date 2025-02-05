/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:33:25 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/05 17:24:05 by anvander         ###   ########.fr       */
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
	while (j <= map->length_max)
	{
		if (x % map->unit_h == 0)
		{
			y = 0;
			while (y <= HEIGHT)
			{
				my_mlx_pixel_put(img, x, y, rgb_to_int(255, 255, 255));
				y++;
			}
		}
		j++;
		x += map->unit_h;
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
		if (y % map->unit_v == 0)
		{
			x = 0;
			while (x <= WIDTH)
			{
				my_mlx_pixel_put(img, x, y, rgb_to_int(255, 255, 255));
				x++;
			}
		}
		i++;
		y += map->unit_v;
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
	(*player)->pos_x = x + map->unit_h / 2;
	(*player)->pos_y = y + map->unit_v / 2;
	(*player)->p_size = map->unit_v / 2;
	(*player)->dist_to_p = map->unit_h / 2 / tan(FOV / 2);
}

void	draw_raycast(t_params *par, t_img *img, t_map *map, double start_x, int color)
{
	double	ray_x = par->player->pos_x;
	double	ray_y = par->player->pos_y;
	double	cos_angle = cos(start_x);
	double	sin_angle = sin(start_x);

	while (is_wall(map, ray_x, ray_y) != '1')
	{
		my_mlx_pixel_put(img, ray_x, ray_y, color);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
		
}

void	draw_fov(t_params *par, t_img *img, t_map *map, t_player *player, int color)
{
	double	fraction;
	double	start_x;
	int		i;

	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_raycast(par, img, map, start_x, color);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, img->img, 0, 0);
}

void    draw_map(t_img *img, t_map *map)
{
    int	j;
	int	i;
	double	x;
	double	y;
	double	saved_x;
	double	saved_y;
	
	i = 0;
	y = 0.0;
	x = 0.0;
	saved_x = x;
	saved_y = y;
	while (i < map->nb_lines)
	{
		j = 0;
		x = 0;
		while (j < map->length_max)
		{
			if (map->map_tab[i][j] && map->map_tab[i][j] == '1')
			{
				y = saved_y;
				while (y <= saved_y + map->unit_v)
				{
					x = saved_x;
					while (x < saved_x + map->unit_h)
					{
						my_mlx_pixel_put(img, x, y, rgb_to_int(128, 128, 128));
						x++;
					}
					y++;
				}
			}
			if (map->map_tab[i][j] && ft_strchr("NEWS", map->map_tab[i][j]))
			{
				draw_player(img, saved_x + map->unit_h / 2, saved_y + map->unit_v / 2, img->player->color);
				init_player_vars(map, &img->player, saved_x, saved_y);
			}
			j++;
			x = j * map->unit_h;
			saved_x = x;
			if (saved_x + map->unit_h > WIDTH)
				saved_x = 0;

		}
		i++;
		y = i * map->unit_v;
		saved_y = y;
	}
}

