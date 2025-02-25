/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:57:11 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/25 12:15:03 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_step(t_raycast *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = (player->pos_x - (double)ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = ((double)ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = (player->pos_y - (double)ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = ((double)ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
}

void	calcul_delta_step(t_raycast *ray, t_player *player)
{
	if (ray->ray_dir_x != 0)
		ray->delta_x = fabs(1 / ray->ray_dir_x);
	else
		ray->delta_x = 1e30;
	if (ray->ray_dir_y != 0)
		ray->delta_y = fabs(1 / ray->ray_dir_y);
	else
		ray->delta_y = 1e30;
	calcul_step(ray, player);
}

void	dda(t_raycast *ray, t_map *map)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->dist_x < ray->dist_y)
		{
			ray->dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x > map->length_max
			|| ray->map_y > map->nb_lines
			|| map->map_tab[ray->map_y][ray->map_x] == '1')
		{
			ray->hit = 1;
			break ;
		}
	}
}

void	find_bottom_top_pixel(t_raycast *ray)
{
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	wall_casting(t_params *par, t_player *player, t_map *map)
{
	int			x;
	int			y;
	t_raycast	*ray;

	ray = par->ray;
	x = 0;
	while (x < WIDTH)
	{
		init_ray(ray, x, player);
		calcul_delta_step(ray, player);
		dda(ray, map);
		remove_fish_eye(ray);
		find_bottom_top_pixel(ray);
		find_column_texture(ray, map, player);
		ray->step = 1.0 * ray->texture->height / ray->line_height;
		ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
			* ray->step;
		y = ray->draw_start;
		draw_column_texture(x, &y, ray, par);
		x++;
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
}
