/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:33:25 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/20 16:37:01 by anvander         ###   ########.fr       */
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

void	draw_floor(t_params *par, t_map *map)
{
	int	y;
	int	x;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(par->img, x, y, map->rgb_floor);
			x++;
		}
		y++;
	}
	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(par->img, x, y, map->rgb_ceil);
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
}

void	find_column_texture(t_raycast *ray, t_map *map, t_player *player)
{
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->texture = map->wall_ea;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->texture = map->wall_no;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->texture = map->wall_so;
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->texture = map->wall_we;
	ray->tex_x = (int)(ray->wall_x * (double)(ray->texture->width));
	ray->tex_x = ray->texture->width - ray->tex_x - 1;
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

void	draw_column_texture(int x, int *y, t_raycast *ray, t_params *par)
{
	while (*y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (ray->texture->height - 1);
		ray->tex_pos += ray->step;
		ray->color = *(int *)(ray->texture->addr
				+ ray->tex_y * ray->texture->l_len
				+ ray->tex_x * (ray->texture->b_pix / 8));
		my_mlx_pixel_put(par->img, x, *y, ray->color);
		(*y)++;
	}
}

void	remove_fish_eye(t_raycast *ray)
{
	if (ray->side == 0)
	ray->perp_wall_dist = ray->sidedist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->sidedist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
}
