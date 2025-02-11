/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:04:52 by anvander          #+#    #+#             */
/*   Updated: 2025/02/11 14:44:19 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float   distance(double x, double y)
{
    return (sqrt(x * x + y * y));
}

/*
a corriger
*/
float   correct_fish_eye(double x1, double y1, double x2, double y2, t_params *par)
{
    double  delta_x;
    double  delta_y;
    double  angle;
    double  fix_dist;
    
    // dprintf(2, "player angle = %f\n", par->player->angle);

    delta_x = x2 - x1;
    delta_y = y2 - y1;
    angle = atan2(delta_y, delta_x) - par->player->angle;
    fix_dist = distance(delta_x, delta_y) * cos(angle);
    return (fix_dist);
}

void	draw_rays(t_params *par, t_img *img, t_map *map, double start_x, int color)
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

void    draw_floor_and_ceilling(t_img *img, int ray, t_map *map)
{
    int i;

    i = map->bot_pix;
    while (i < HEIGHT)
    {
        my_mlx_pixel_put(img, ray, i, map->rgb_floor);
        i++;
    }
    i = 0;
    while (i < map->top_pix)
    {
        my_mlx_pixel_put(img, ray, i, map->rgb_ceil);
        i++;       
    }
}
#define M_PI       3.14159265358979323846
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)
/*
Cosinus  - sinus
plus un angle est petit plus son cosinus est grand et plus on avance sur un axe horizontal (x), 
plus le rayon va rencontrer de lignes verticales avant de touchr un mur
donc quand le cosinus > sinus -> mur rencontre par la verticale
*/
void	draw_lines_3d(t_params *par, t_img *img, t_map *map, double start_x, int ray, int color)
{
	double	ray_x = par->player->pos_x;
	double	ray_y = par->player->pos_y;
	double	cos_angle = cos(start_x);
	double	sin_angle = sin(start_x);
    double  dist;
    double  start_y;
    double  end;
    double  text_x;
    int  text_y;
    double  incr_y;
    (void)color;
    
    start_y = 0;
    end = 0;
    dist = 0;
    text_x = 0;
    text_y = 0;
    
	while (is_wall(map, ray_x, ray_y) != '1')
	{
        ray_x += cos_angle;
		ray_y += sin_angle;
	}
    dist = correct_fish_eye(par->player->pos_x, par->player->pos_y, ray_x, ray_y, par);
    
    // hauteur du mur
    map->height = (par->map->unit_v / dist) * (WIDTH / 2);
    map->top_pix = (HEIGHT / 2) - (map->height / 2);
    map->bot_pix = (HEIGHT / 2) + (map->height / 2);
    start_y = map->top_pix;
    end = map->bot_pix;
    
    // pour trouver la colonne de texture
    if ((cos_angle) > (sin_angle))
        text_x = fmod(ray_y, par->map->unit_v) / par->map->unit_v * map->wall_no->width;
    else
        text_x = fmod(ray_x, par->map->unit_h) / par->map->unit_h * map->wall_no->width;
     
        
    incr_y = 0;
    while (start_y < end)
    {
        text_y = (int)incr_y % map->wall_no->height;
        incr_y += (double)map->wall_no->height / map->height;
        color = *(int *)(map->wall_no->addr + text_y * map->wall_no->l_len + (int)text_x * (map->wall_no->b_pix / 8));
        my_mlx_pixel_put(img, ray, start_y, color);            
        start_y++;
    }
}

void	draw_lines_2d(t_params *par, t_img *img, t_map *map, double start_x, int color)
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

void	draw_3d(t_params *par, t_img *img, t_map *map, t_player *player, int color)
{
	double fraction;
	double	start_x;
	int		ray;

	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	ray = 0;
	while (ray < WIDTH)
	{
        draw_floor_and_ceilling(img, ray, map);
		draw_lines_3d(par, img, map, start_x, ray, color);
		start_x += fraction;
		ray++;
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, img->img, 0, 0);
    
}

void	draw_fov(t_params *par, t_img *img, t_map *map, t_player *player, int color)
{
	double fraction;
	double	start_x;
	int		i;

	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
    dprintf(2, "%s, %d\n", __FILE__, __LINE__);
	while (i < WIDTH)
	{
		draw_lines_2d(par, img, map, start_x, color);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, img->img, WIDTH - WIDTH_MINI, HEIGHT - HEIGHT_MINI);
}
/*
1. Finding the coordinate of A.  
   If the ray is facing up      
     A.y = rounded_down(Py/64) * (64) - 1;wwwwssss
   If the ray is facing down
     A.y = rounded_down(Py/64) * (64) + 64;

   (In the picture, the ray is facing up, so we use
   the first formula.  
   A.y=rounded_down(224/64) * (64) - 1 = 191;
   Now at this point, we can find out the grid 
   coordinate of y.
   However, we must decide whether A is part of 
   the block above the line,
   or the block below the line.  
   Here, we chose to make A part of the block
   above the line, that is why we subtract 1 from A.y.
   So the grid coordinate of A.y is 191/64 = 2;

   A.x = Px + (Py-A.y)/tan(ALPHA);
   In the picture, (assume ALPHA is 60 degrees), 
   A.x=96 + (224-191)/tan(60) = about 115;
   The grid coordinate of A.x is 115/64 = 1;

   So A is at grid (1,2) and we can check 
   whether there is a wall on that grid.
   There is no wall on (1,2) so the ray will be 
   extended to C.

2. Finding Ya
   If the ray is facing up      
     Ya=-64;
   If the ray is facing down
     Ya=64;

3. Finding Xa
   Xa = 64/tan(60) = 36;

4. We can get the coordinate of C as follows:
   C.x=A.x+Xa = 115+36 = 151;
   C.y=A.y+Ya = 191-64 = 127;
   Convert this into grid coordinate by 
   dividing each component with 64.  
   The result is 
   C.x = 151/64 = 2 (grid coordinate), 
   C.y = 127/64 = 1 (grid coordinate) 
   So the grid coordinate of C is (2, 1).  
   (C programmer's note: Remember we always round down, 
   this is especially true since
   you can use right shift by 8 to divide by 64).

5. Grid (2,1) is checked.  
   Again, there is no wall, so the ray is extended 
   to D.  
   
6. We can get the coordinate of D as follows:
   D.x=C.x+Xa = 151+36 = 187;
   D.y=C.y+Ya = 127-64 = 63;
   Convert this into grid coordinate by 
   dividing each component with 64.  
   The result is 
   D.x = 187/64 = 2 (grid coordinate), 
   D.y = 63/64 = 0 (grid coordinate) 
   So the grid coordinate of D is (2, 0).  

6. Grid (2,0) is checked.  
   There is a wall there, so the process stop.
*/
// double  get_h_inter(t_params *par, double start_x)
// {
    
// }

// void	cast_rays(t_params *par, t_img *img, t_map *map, t_player *player, int color)
// {
//     double  h_inter;
//     double  v_inter;
// 	double fraction;
// 	double	start_x;
// 	int		i;

// 	fraction = PI / 3 / WIDTH;
// 	start_x = player->angle - (FOV / 2);
// 	i = 0;
// 	while (i < WIDTH)
// 	{
//         h_inter = get_h_inter(par, start_x);
//         v_inter = get_v_inter(par, start_x);
//         if (v_inter <= h_inter)
//             par->ray->distance = v_inter;
//         else
//         {
//             par->ray->distance = h_inter;
//             par->ray->flag = 1;
//         }
// 		start_x += fraction;
// 		i++;
// 	}
// }