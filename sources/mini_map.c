/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:14:31 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/19 17:47:53 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img *img, double x, double y, int color)
{
	int	i;
	int	j;
	char	*pixel_color;
	
	i = -2;
	j = -2;
	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{
			pixel_color = img->addr + ((int)y - j) * img->l_len + ((int)x - i) * (img->b_pix / 8);
			if (*(int *)pixel_color != rgb_to_int(128, 128, 128))
			{
				my_mlx_pixel_put(img, x - i,  y - j, color);
				j++;
			}
			else	
				break ;
		}
		i++;
	}
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
	double	saved_x;
	
	j = 0;
	x = 0.0;
	saved_x = x;
	while (j < map->length_max)
	{
		if (map->map_tab[i][j] && map->map_tab[i][j] == '1')
			draw_walls(mini_map, map, &x, &y, saved_x, saved_y);
		if (map->map_tab[i][j] && ft_strchr("NEWS", map->map_tab[i][j]))
		{
			player->mini_pos_x = (double)saved_x + 0.5; //
			player->mini_pos_y = (double)saved_y + 0.5;
			draw_player(mini_map, player->mini_pos_x, player->mini_pos_y, rgb_to_int(255, 0, 0));
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

char	is_wall(t_map *map, double new_x, double new_y)
{
	int	grid_x;
	int	grid_y;
	char	ret;

	grid_x = (int)(new_x / map->unit_h_mini);
	grid_y = (int)(new_y / map->unit_v_mini);
	ret = map->map_tab[grid_y][grid_x];
	return (ret);
}

// void	draw_rays(t_params *par, t_img *img, t_map *map, double start_x, int color) // mini_map
// {
// 	double	ray_x = par->player->pos_x;
// 	double	ray_y = par->player->pos_y;
// 	double	cos_angle = cos(start_x);
// 	double	sin_angle = sin(start_x);

// 	while (is_wall(map, ray_x, ray_y) != '1')
// 	{
// 		my_mlx_pixel_put(img, ray_x, ray_y, color);
// 		ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}
// }

// void	draw_lines_2d(t_params *par, t_img *img, t_map *map, double start_x, int color) // mini_map
// {
// 	double	ray_x = par->player->mini_pos_x;
// 	double	ray_y = par->player->mini_pos_y;
// 	double	cos_angle = cos(start_x);
// 	double	sin_angle = sin(start_x);

// 	while (is_wall(map, ray_x, ray_y) != '1')
// 	{
//         my_mlx_pixel_put(img, ray_x, ray_y, color);
//         ray_x += cos_angle;
// 		ray_y += sin_angle;
// 	}	
// }

// void	draw_fov(t_params *par, t_img *img, t_map *map, t_player *player, int color)
// {
// 	double fraction;
// 	double	start_x;
// 	int		i;

// 	fraction = PI / 3 / WIDTH;
// 	start_x = player->angle - PI / 6;
// 	i = 0;
// 	while (i < WIDTH)
// 	{
// 		draw_lines_2d(par, img, map, start_x, color);
// 		start_x += fraction;
// 		i++;
// 	}
// 	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, img->img, WIDTH - WIDTH_MINI, HEIGHT - HEIGHT_MINI);
// }
