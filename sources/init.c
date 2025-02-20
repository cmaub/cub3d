/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:30:57 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/20 16:18:30 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_ray(t_raycast *ray, int x, t_player *player)
{
    ray->camera_x = 2 * x / (double)WIDTH - 1;
    ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
    ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;
    ray->sidedist_x = 0;
    ray->sidedist_y = 0;
    ray->delta_dist_x = 0;
    ray->delta_dist_y = 0;
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

void	get_texture_path(t_map *map)
{
	map->wall_no->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_no,
				&map->wall_no->width, &map->wall_no->height);
	map->wall_so->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_so,
				&map->wall_so->width, &map->wall_so->height);
	map->wall_ea->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_ea,
				&map->wall_ea->width, &map->wall_ea->height);
	map->wall_we->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_we,
				&map->wall_we->width, &map->wall_we->height);
	if (!map->wall_no->img || !map->wall_so->img || !map->wall_ea->img || !map->wall_we->img)
	{
		printf("Error\nwith xpm files\n");
		close_window(map->par);
	}	
}

void	get_texture_address(t_map *map)
{
	map->wall_no->addr = mlx_get_data_addr(map->wall_no->img, &map->wall_no->b_pix, 
					&map->wall_no->l_len, &map->wall_no->endian);
	map->wall_ea->addr = mlx_get_data_addr(map->wall_ea->img, &map->wall_ea->b_pix, 
					&map->wall_ea->l_len, &map->wall_ea->endian);
	map->wall_so->addr = mlx_get_data_addr(map->wall_so->img, &map->wall_so->b_pix, 
					&map->wall_so->l_len, &map->wall_so->endian);
	map->wall_we->addr = mlx_get_data_addr(map->wall_we->img, &map->wall_we->b_pix, 
					&map->wall_we->l_len, &map->wall_we->endian);					
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

void    init_structs(t_params *par)
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
	img->width = WIDTH;
	img->height = HEIGHT;
	mini_map->width = WIDTH_MINI;
	mini_map->height = HEIGHT_MINI;
    img->img = mlx_new_image(par->mlx_ptr, img->width, img->height);
	mini_map->img = mlx_new_image(par->mlx_ptr, mini_map->width, mini_map->height);
    if (!img->img)
        close_window(par);
    img->addr = mlx_get_data_addr(img->img, &img->b_pix, &img->l_len, &img->endian);
	mini_map->addr = mlx_get_data_addr(mini_map->img, &mini_map->b_pix, &mini_map->l_len, &mini_map->endian);
    par->player->color = rgb_to_int(255, 0, 0);
	par->player->angle = par->map->player->angle;
}
