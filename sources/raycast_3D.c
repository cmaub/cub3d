/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:57:11 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/19 16:19:12 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    floor_casting(t_params *par, t_map *map)
{
    int y;
    int x;

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
    y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_mlx_pixel_put(par->img, x, y, map->rgb_ceil);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
}

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

void    calcul_step(t_raycast *ray, t_player *player)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->sidedist_x = (player->pos_x - (double)ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->sidedist_x = ((double)ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->sidedist_y = (player->pos_y - (double)ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->sidedist_y = ((double)ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
    }
}

void    calcul_delta_step(t_raycast *ray, t_player *player)
{
    if (ray->ray_dir_x != 0)
        ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    else 
        ray->delta_dist_x = 1e30;
    if (ray->ray_dir_y != 0)
        ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
    else
        ray->delta_dist_y = 1e30;
    calcul_step(ray, player);
}

void    dda(t_raycast *ray, t_map *map)
{
    ray->hit = 0;
    while (ray->hit == 0)
    {
        if (ray->sidedist_x < ray->sidedist_y)
        {
            ray->sidedist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->sidedist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (ray->map_x < 0 || ray->map_x > map->length_max 
            || ray->map_y > map->nb_lines || map->map_tab[ray->map_y][ray->map_x] == '1')
        {
            ray->hit = 1;
            break ;
        }
    }
}

void    remove_fish_eye(t_raycast *ray)
{
    if (ray->side == 0)
    ray->perp_wall_dist = ray->sidedist_x - ray->delta_dist_x;
    else
        ray->perp_wall_dist = ray->sidedist_y - ray->delta_dist_y;
    ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
}

void    find_bottom_top_pixel(t_raycast *ray)
{
    ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_start < 0)
        ray->draw_start = 0;
    ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
    if (ray->draw_end >= HEIGHT)
        ray->draw_end = HEIGHT - 1;
}

void    find_column_texture(t_raycast *ray, t_map *map, t_player *player)
{
    if (ray->side == 0)
        ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    ray->wall_x -= floor(ray->wall_x); // partie fractionnaire de ray->wall_x
    
    //Calculate texture
    if (ray->side == 0 && ray->ray_dir_x > 0)
        ray->texture = map->wall_ea;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        ray->texture = map->wall_no;
    if (ray->side == 1 && ray->ray_dir_y > 0)
        ray->texture = map->wall_so;
    if (ray->side == 0 && ray->ray_dir_x < 0)
        ray->texture = map->wall_we;

    //x coordinate on the ray->texture
    ray->tex_x = (int)(ray->wall_x * (double)(ray->texture->width));
    if (ray->side == 0 && ray->ray_dir_x > 0)
        ray->tex_x = ray->texture->width - ray->tex_x - 1;
    if (ray->side == 1 && ray->ray_dir_y < 0)
        ray->tex_x = ray->texture->width - ray->tex_x - 1;
}

void    draw_column_texture(int x, int *y, t_raycast *ray, t_params *par)
{
    while (*y < ray->draw_end)
    {
        ray->tex_y = (int)ray->tex_pos & (ray->texture->height - 1);
        ray->tex_pos += ray->step;
        ray->color = *(int *)(ray->texture->addr + ray->tex_y * ray->texture->l_len + ray->tex_x * (ray->texture->b_pix / 8));
        my_mlx_pixel_put(par->img, x, *y, ray->color);
        (*y)++;
    }
}

void    wall_casting(t_params *par, t_player *player, t_map *map)
{
    int     x;
    int     y;
    t_raycast *ray;
    
    ray = clean_malloc(sizeof(t_raycast), par);
    
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
        ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * ray->step;
        y = ray->draw_start;
        draw_column_texture(x, &y, ray, par);
        x++;
    }
    mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
}
