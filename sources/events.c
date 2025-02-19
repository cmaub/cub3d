/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:04:24 by anvander          #+#    #+#             */
/*   Updated: 2025/02/19 17:30:01 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*
Move player unless the next move will make us hit a wall
*/
int	check_hit_and_update(t_map *map, double x, double y, t_player **player)
{
	if (map->map_tab[(int)y][(int)x] != '1')
	{
		(*player)->pos_x = x;
		(*player)->pos_y = y;
		return (TRUE);
	}
	return (FALSE);
}

void	check_hit_and_update_mini(t_map *map, double mini_x, double mini_y, t_player **player)
{
	(void)map;
	// int	i;
	// int	j;
	
	// i = -2;
	// while (i < 3)
	// {
	// 	j = -2;
	// 	while (j < 3)
	// 	{
	// 		if (is_wall(map, mini_x - i, mini_y - j) != '1')
	// 			j++;
	// 		else
	// 		{
	// 			// dprintf(2, "i = %d, j = %d\n", i, j);
	// 			return;
	// 		}
	// 	}
	// 	i++;
	// }
	(*player)->mini_pos_x = mini_x;
	(*player)->mini_pos_y = mini_y;
}

int	move(t_map *map, t_player **player, double dist)
{
	double	new_mini_x;
	double	new_mini_y;

	new_mini_x = 0;
	new_mini_y = 0;
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	dprintf(2, "**** pos_x = %f, pos_y = %f, mini_pos_x = %f, min->pos-y = %f\n", (*player)->pos_x, (*player)->pos_y, (*player)->mini_pos_x, (*player)->mini_pos_y);

	(*player)->angle = atan2((*player)->dir_y, (*player)->dir_x);
	if ((*player)->angle < 0)
		(*player)->angle += 2 * PI;
	if ((*player)->move_up)
	{
		new_x = (*player)->pos_x + cos((*player)->angle) * dist;
		new_y = (*player)->pos_y + sin((*player)->angle) * dist;
		new_mini_x = (*player)->mini_pos_x + cos((*player)->angle) * dist * map->unit_h_mini;
		dprintf(2, "new_mini_x = %f\n", new_mini_x);
		new_mini_y = (*player)->mini_pos_y + sin((*player)->angle) * dist * map->unit_v_mini;
		// new_mini_y = (*player)->mini_pos_y * dist * map->unit_h_mini;
		dprintf(2, "new_mini_y = %f\n", new_mini_y);
	}
	else if ((*player)->move_down)
	{
		new_x = (*player)->pos_x - cos((*player)->angle) * dist;
		new_y = (*player)->pos_y - sin((*player)->angle) * dist;
		new_mini_x = (*player)->mini_pos_x - cos((*player)->angle) * dist * map->unit_h_mini;
		new_mini_y = (*player)->mini_pos_y - sin((*player)->angle) * dist * map->unit_v_mini;
		// new_mini_y = (*player)->mini_pos_y * dist * map->unit_h_mini;
	}	
	else if ((*player)->move_left)
	{
		new_x = (*player)->pos_x + sin((*player)->angle) * dist;
		new_y = (*player)->pos_y - cos((*player)->angle) * dist;
		new_mini_x = (*player)->mini_pos_x + sin((*player)->angle) * dist * map->unit_h_mini;
		new_mini_y = (*player)->mini_pos_y - cos((*player)->angle) * dist * map->unit_v_mini;
	}
	else if ((*player)->move_rigth)
	{
		new_x = (*player)->pos_x - sin((*player)->angle) * dist;
		new_y = (*player)->pos_y + cos((*player)->angle) * dist;
		new_mini_x = (*player)->mini_pos_x - sin((*player)->angle) * dist  * map->unit_h_mini;
		new_mini_y = (*player)->mini_pos_y + cos((*player)->angle) * dist * map->unit_v_mini;
	}
	if (!check_hit_and_update(map, new_x, new_y, player))
		return (FALSE);
	check_hit_and_update_mini(map, new_mini_x, new_mini_y, player);
	dprintf(2, "pos_x = %f, pos_y = %f, mini_pos_x = %f, min->pos-y = %f\n", (*player)->pos_x, (*player)->pos_y, (*player)->mini_pos_x, (*player)->mini_pos_y);
	return (TRUE);
}

// void	move_mini(t_map *map, t_player **player, double dist)
// {
// 	double	new_mini_x;
// 	double	new_mini_y;

// 	new_mini_x = 0;
// 	new_mini_y = 0;
// 	// (*player)->angle = atan2((*player)->dir_y, (*player)->dir_x);
// 	// if ((*player)->angle < 0)
// 	// 	(*player)->angle += 2 * PI;
// 	if ((*player)->move_up)
// 	{
// 		// new_x = (*player)->pos_x + cos((*player)->angle) * dist;
// 		// new_y = (*player)->pos_y + sin((*player)->angle) * dist;
// 		// new_mini_x = (*player)->mini_pos_x + cos((*player)->angle) * dist;
// 		// new_mini_y = (*player)->mini_pos_y + sin((*player)->angle) * dist;
// 	}
// 	else if ((*player)->move_down)
// 	{
// 		// new_x = (*player)->pos_x - cos((*player)->angle) * dist;
// 		// new_y = (*player)->pos_y - sin((*player)->angle) * dist;
// 		new_mini_x = (*player)->mini_pos_x - cos((*player)->angle) * dist;
// 		new_mini_y = (*player)->mini_pos_y - sin((*player)->angle) * dist;
// 	}	
// 	else if ((*player)->move_left)
// 	{
// 		// new_x = (*player)->pos_x + sin((*player)->angle) * dist;
// 		// new_y = (*player)->pos_y - cos((*player)->angle) * dist;
// 		new_mini_x = (*player)->mini_pos_x + sin((*player)->angle) * dist;
// 		new_mini_y = (*player)->mini_pos_y - cos((*player)->angle) * dist;
// 	}
// 	else if ((*player)->move_rigth)
// 	{
// 		// new_x = (*player)->pos_x - sin((*player)->angle) * dist;
// 		// new_y = (*player)->pos_y + cos((*player)->angle) * dist;
// 		new_mini_x = (*player)->mini_pos_x - sin((*player)->angle) * dist;
// 		new_mini_y = (*player)->mini_pos_y + cos((*player)->angle) * dist;
// 	}
// 	check_hit_and_update_mini(map, new_mini_x, new_mini_y, player);
// }

void	rotate_left(t_player **player, double *old_dir_x, double *old_plane_x, double distance)
{
	(*player)->angle -= distance;
	if ((*player)->angle < 0)
		(*player)->angle += 2 * PI;
	*old_dir_x = (*player)->dir_x;
	(*player)->dir_x = (*player)->dir_x * cos( -distance / 4) - (*player)->dir_y * sin(-distance / 4);
	(*player)->dir_y = (*old_dir_x) * sin(-distance / 4) + (*player)->dir_y * cos(-distance / 4);
	(*old_plane_x) = (*player)->plane_x;
	(*player)->plane_x = (*player)->plane_x * cos(-distance / 4) - (*player)->plane_y * sin(-distance / 4);
	(*player)->plane_y = (*old_plane_x) * sin(-distance / 4) + (*player)->plane_y * cos(-distance / 4);
}

void	rotate_right(t_player **player, double *old_dir_x, double *old_plane_x, double distance)
{
	(*player)->angle += distance;
	if ((*player)->angle > 2 * PI)
		(*player)->angle -= 2 * PI;
	*old_dir_x = (*player)->dir_x;
	(*player)->dir_x = (*player)->dir_x * cos(distance / 4) - (*player)->dir_y * sin(distance / 4);
	(*player)->dir_y = *old_dir_x * sin(distance / 4) + (*player)->dir_y * cos(distance / 4);
	*old_plane_x = (*player)->plane_x;
	(*player)->plane_x = (*player)->plane_x * cos(distance / 4) - (*player)->plane_y * sin(distance / 4);
	(*player)->plane_y = *old_plane_x * sin(distance / 4) + (*player)->plane_y * cos(distance / 4);
}

void	rotate(t_player **player, double distance)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = 0;
	old_plane_x = 0;
	if ((*player)->rotate_left)
		rotate_left(player, &old_dir_x, &old_plane_x, distance);
	else if ((*player)->rotate_rigth)
		rotate_right(player, &old_dir_x, &old_plane_x, distance);
}

int	key_update(t_params *par)
{    
	if (par->player->move_up || par->player->move_down || par->player->move_rigth || par->player->move_left)
	{
		draw_player(par->mini_map, par->player->mini_pos_x, par->player->mini_pos_y, 0);
		// draw_fov(par, par->mini_map, par->map, par->player, 0);
		// if (move(par->map, &par->player, 0.5))
		// 	move_mini(par->map, &par->player, 0.5);
		move(par->map, &par->player, 0.5);
		draw_player(par->mini_map, par->player->mini_pos_x, par->player->mini_pos_y, par->player->color);
		// draw_fov(par, par->mini_map, par->map, par->player, 255);
		// draw_3d(par, par->img, par->map, par->player, 255);
		floor_casting(par, par->map);
		wall_casting(par, par->player, par->map);
	}
	else if (par->player->rotate_left || par->player->rotate_rigth)
	{
		draw_player(par->mini_map, par->player->mini_pos_x, par->player->mini_pos_y, 0);
		// draw_fov(par, par->mini_map, par->map, par->player, 0);
		rotate(&par->player, PI / 6.0);
		draw_player(par->mini_map, par->player->mini_pos_x, par->player->mini_pos_y, par->player->color);
		// draw_fov(par, par->mini_map, par->map, par->player, 255);
		// draw_3d(par, par->img, par->map, par->player, 255);
		floor_casting(par, par->map);
		wall_casting(par, par->player, par->map);
	}
	// draw_vertical_grid(par->mini_map, par->map);
	// draw_horizontal_grid(par->mini_map, par->map);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->mini_map->img, WIDTH - WIDTH_MINI, HEIGHT - HEIGHT_MINI);
	return (0);
}

int	key_press(int keycode, t_params *par)
{
	if (keycode == KEY_ESC)
        close_window(par);
	if (keycode == W)
		par->player->move_up = 1;
	else if (keycode == S)
		par->player->move_down = 1;
	else if (keycode == A)
		par->player->move_left = 1;
	else if (keycode == D)
		par->player->move_rigth = 1;
	else if (keycode == LEFT)
		par->player->rotate_left = 1;
	else if (keycode == RIGHT)
		par->player->rotate_rigth = 1;
	return (0);
}

int	key_release(int keycode, t_params *par)
{
	if (keycode == W)
		par->player->move_up = 0;
	else if (keycode == S)
		par->player->move_down = 0;
	else if (keycode == A)
		par->player->move_left = 0;
	else if (keycode == D)
		par->player->move_rigth = 0;
	else if (keycode == LEFT)
		par->player->rotate_left = 0;
	else if (keycode == RIGHT)
		par->player->rotate_rigth = 0;
	return (0);
}
