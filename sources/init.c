/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:30:57 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/21 16:44:51 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_raycast *ray, int x, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->dist_x = 0;
	ray->dist_y = 0;
	ray->delta_x = 0;
	ray->delta_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->wall_x = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->tex_pos = 0;
	ray->step = 0;
	ray->color = 0;
	ray->texture = 0;
}

void	init_t_map(t_params *par)
{
	par->fd = -1;
	par->map = clean_malloc(sizeof(t_map), par);
	par->player = clean_malloc(sizeof(t_player), par);
	par->map->player = par->player;
	par->map->length_max = 0;
	par->map->nb_lines = 0;
	par->map->rgb_floor = -1;
	par->map->rgb_ceil = -1;
	par->map->path_no = NULL;
	par->map->path_so = NULL;
	par->map->path_ea = NULL;
	par->map->path_we = NULL;
	par->ray = clean_malloc(sizeof(t_raycast), par);
}

void	init_map(t_params *par)
{
	par->map->wall_no = clean_malloc(sizeof(t_img), par);
	par->map->wall_so = clean_malloc(sizeof(t_img), par);
	par->map->wall_ea = clean_malloc(sizeof(t_img), par);
	par->map->wall_we = clean_malloc(sizeof(t_img), par);
	par->mini_map = clean_malloc(sizeof(t_img), par);
	par->map->height = 0;
	par->map->par = par;
	par->mlx_ptr = NULL;
	par->win_ptr = NULL;
	par->mlx_ptr = mlx_init();
	get_texture_path(par->map);
	get_texture_address(par->map);
}

void	init_structs(t_params *par)
{
	t_img	*img;
	t_img	*mini_map;

	par->img = clean_malloc(sizeof(t_img), par);
	init_map(par);
	par->img->player = par->player;
	img = par->img;
	mini_map = par->mini_map;
	if (!par->mlx_ptr)
		close_window(par);
	par->win_ptr = mlx_new_window(par->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	if (!par->win_ptr)
		close_window(par);
	init_images(par, img, mini_map);
	par->player->color = rgb_to_int(255, 0, 0);
	par->player->angle = par->map->player->angle;
}
