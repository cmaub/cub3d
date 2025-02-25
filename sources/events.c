/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:04:24 by anvander          #+#    #+#             */
/*   Updated: 2025/02/25 14:23:00 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit_and_exit(t_map *map, double x, double y, t_player **player)
{
	if (map->map_tab[(int)y][(int)x] != '1')
	{
		(*player)->pos_x = x;
		(*player)->pos_y = y;
		return (TRUE);
	}
	return (FALSE);
}

int	key_update(t_params *par)
{
	if (par->player->move_up || par->player->move_down
		|| par->player->move_rigth || par->player->move_left)
	{
		move(par->map, &par->player, 0.065);
		draw_floor(par, par->map);
		wall_casting(par, par->player, par->map);
	}
	else if (par->player->left || par->player->rotate_rigth)
	{
		rotate(&par->player, PI / 36.0);
		draw_floor(par, par->map);
		wall_casting(par, par->player, par->map);
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
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
		par->player->left = 1;
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
		par->player->left = 0;
	else if (keycode == RIGHT)
		par->player->rotate_rigth = 0;
	return (0);
}
