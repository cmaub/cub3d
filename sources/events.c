/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:04:24 by anvander          #+#    #+#             */
/*   Updated: 2025/02/13 16:25:23 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_wall(t_map *map, double new_x, double new_y)
{
	int	grid_x;
	int	grid_y;
	char	ret;

	grid_x = (int)(new_x / map->unit_h_mini);
	grid_y = (int)(new_y / map->unit_v_mini);
	ret = map->map_tab[grid_y][grid_x];
	// if (grid_x < 0 || grid_x >= map->length_max || grid_y < 0 || grid_y >= map->nb_lines)
	// 	return (49);
	return (ret);
}

/*
Move player unless the next move will make us hit a wall
*/
void	check_hit_and_update(t_map *map, double x, double y, t_player **player)
{
	int	i;
	int	j;
	
	i = -2;
	j = -2;
	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{
			if (is_wall(map, x - i, y - j) != '1')
				j++;
			else
				return ;
		}
		i++;
	}
	if (i == 3 && j == 3)
	{
		(*player)->pos_x = x;
		(*player)->pos_y = y;
	}
}

/*
W => move up
S => move down
A => move to the right
D => move to the left
*/
void	move(t_map *map, t_player **player, double dist, int keycode)
{
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	if (keycode == W)
	{
		new_x = roundf((*player)->pos_x + cos((*player)->angle) * dist);
		new_y = roundf((*player)->pos_y + sin((*player)->angle) * dist);
	}
	else if (keycode == S)
	{
		new_x = roundf((*player)->pos_x - cos((*player)->angle) * dist);
		new_y = roundf((*player)->pos_y - sin((*player)->angle) * dist);
	}	
	else if (keycode == A)
	{
		new_x = roundf((*player)->pos_x + sin((*player)->angle) * dist);
		new_y = roundf((*player)->pos_y - cos((*player)->angle) * dist);
	}
	else if (keycode == D)
	{
		new_x = roundf((*player)->pos_x - sin((*player)->angle) * dist);
		new_y = roundf((*player)->pos_y + cos((*player)->angle) * dist);
	}
	check_hit_and_update(map, new_x, new_y, player);
}

void	rotate(t_player **player, double distance, int keycode)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos((*player)->angle);
	sin_angle = sin((*player)->angle);
	if (keycode == LEFT)
	{
		(*player)->angle -= distance;
		if ((*player)->angle < 0)
			(*player)->angle += 2 * PI;
	}
	else if (keycode == RIGHT)
	{
		(*player)->angle += distance;
		if ((*player)->angle > 2 * PI)
			(*player)->angle -= 2 * PI;
	}

}

int	close_window(t_params *par)
{
	if (!par)
	{
		exit(1);
		return (0);
	}
	if (par->img)
		mlx_destroy_image(par->mlx_ptr, par->img->img);
	if (par->win_ptr)
		mlx_destroy_window(par->mlx_ptr, par->win_ptr);
	if (par->mlx_ptr)
	{
		mlx_destroy_display(par->mlx_ptr);
		free(par->mlx_ptr);
		free(par);
	}
	exit(1);
	return (0);
}

int	key_event(int keycode, t_params *par)
{
    if (keycode == KEY_ESC)
        close_window(par);
	else if ((keycode == W) || (keycode == S) || (keycode == A) || (keycode == D))
	{
		dprintf(2, "line %d, file %s\n", __LINE__, __FILE__);
		draw_player(par->mini_map, par->player->pos_x, par->player->pos_y, 0);
		draw_fov(par, par->mini_map, par->map, par->player, 0);
		clear_image(par);
		move(par->map, &par->player, 10, keycode);
		draw_player(par->mini_map, par->player->pos_x, par->player->pos_y, par->player->color);
		draw_fov(par, par->mini_map, par->map, par->player, 255);
		// draw_3d(par, par->img, par->map, par->player, 255);
		// floor_casting(par, par->player, par->map);
		wall_casting(par, par->player, par->map);
	}
	else if ((keycode == LEFT) || (keycode == RIGHT))
	{
		draw_player(par->mini_map, par->player->pos_x, par->player->pos_y, 0);
		draw_fov(par, par->mini_map, par->map, par->player, 0);
		clear_image(par);
		rotate(&par->player, 0.2, keycode);
		draw_player(par->mini_map, par->player->pos_x, par->player->pos_y, par->player->color);
		draw_fov(par, par->mini_map, par->map, par->player, 255);
		// draw_3d(par, par->img, par->map, par->player, 255);
		// floor_casting(par, par->player, par->map);
		wall_casting(par, par->player, par->map);
	}
	draw_vertical_grid(par->mini_map, par->map);
	draw_horizontal_grid(par->mini_map, par->map);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->mini_map->img, WIDTH - WIDTH_MINI, HEIGHT - HEIGHT_MINI);
	
	return (0);
}
