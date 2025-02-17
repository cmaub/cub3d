/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3D.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:57:11 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/17 14:29:26 by cmaubert         ###   ########.fr       */
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

void    wall_casting(t_params *par, t_player *player, t_map *map)
{
    int     x;
    int     y;
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  sidedist_x;
    double  sidedist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
    int     line_height = 0;
    int     draw_start;
    int     draw_end;
    double  wall_x;
    // int     tex_num;
    int     tex_x;
    int     tex_y;
    double  tex_pos;
    double  step;
    int     color;
    t_img   *texture;
    // double  length;
    
    x = 0;
    hit = 0;
    while (x < WIDTH)
    {
        camera_x = 2 * x / (double)WIDTH - 1;
        ray_dir_x = player->dir_x + player->plane_x * camera_x;
        ray_dir_y = player->dir_y + player->plane_y * camera_x;
        
        map_x = (int)par->player->pos_x;
        map_y = (int)par->player->pos_y;
        // dprintf(2, "map_x %d, map_y %d, player->pox_x = %f, player->pos_y = %f\n", map_x, map_y, player->pos_x, player->pos_y);
        
        if (ray_dir_x != 0)
            delta_dist_x = fabs(1 / ray_dir_x);
        else 
            delta_dist_x = 1e30;
        if (ray_dir_y != 0)
            delta_dist_y = fabs(1 / ray_dir_y);
        else
            delta_dist_y = 1e30;
        
        // calcul du step
        if (ray_dir_x < 0)
        {
            step_x = -1;
            sidedist_x = (player->pos_x - (double)map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            sidedist_x = ((double)map_x + 1.0 - player->pos_x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            sidedist_y = (player->pos_y - (double)map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            sidedist_y = ((double)map_y + 1.0 - player->pos_y) * delta_dist_y;
        }
        // perform DDA
        
        hit = 0;
        while (hit == 0)
        {
            if (sidedist_x < sidedist_y)
            {
                sidedist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                sidedist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map_x < 0 || map_x > map->length_max || map_y > map->nb_lines || map->map_tab[map_y][map_x] == '1')
            {
                hit = 1;
                break ;
            }
        }
        
        //calculate the distance of perpendicular ray to remove fish eye
        if (side == 0)
            perp_wall_dist = sidedist_x - delta_dist_x;
        else
            perp_wall_dist = sidedist_y - delta_dist_y;
        
        line_height = (int)(HEIGHT / perp_wall_dist);
    
        //Calculate bottom pixel and top pixel to fill in current column
        draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT)
            draw_end = HEIGHT - 1;
    
        //Calculate value of wall_x
        if (side == 0)
            wall_x = player->pos_y + perp_wall_dist * ray_dir_y;
        else
            wall_x = player->pos_x + perp_wall_dist * ray_dir_x;
        wall_x -= floor(wall_x); // partie fractionnaire de wall_x

        //Calculate texture
        if (side == 0 && ray_dir_x > 0)
            texture = map->wall_ea;
        if (side == 1 && ray_dir_y < 0)
            texture = map->wall_no;
        if (side == 1 && ray_dir_y > 0)
            texture = map->wall_so;
        if (side == 0 && ray_dir_x < 0)
            texture = map->wall_we;
            
        //x coordinate on the texture
        tex_x = (int)(wall_x * (double)(texture->width));
        if (side == 0 && ray_dir_x > 0)
            tex_x = texture->width - tex_x - 1;
        if (side == 1 && ray_dir_y < 0)
            tex_x = texture->width - tex_x - 1;

        //calculate step per screen pixel
        step = 1.0 * texture->height / line_height;
        
        tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
        y = draw_start;
        while (y < draw_end)
        {
            tex_y = (int)tex_pos & (texture->height - 1);
            tex_pos += step;
            color = *(int *)(texture->addr + tex_y * texture->l_len + tex_x * (texture->b_pix / 8));
            my_mlx_pixel_put(par->img, x, y, color);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
}