/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 15:04:24 by anvander          #+#    #+#             */
/*   Updated: 2025/02/25 15:35:45 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	mouse_event(int x, int y, t_params *par)
{
	float	delta_x;

	(void)y;
	delta_x = (float)(x - WIDTH / 2);
	rotate_mouse(&par->player, PI / 36.0, delta_x);
	mlx_mouse_move(par->mlx_ptr, par->win_ptr, WIDTH / 2, HEIGHT / 2);
	return (0);
}

int	key_update(t_params *par)
{
	if (par->player->move_up || par->player->move_down
		|| par->player->move_rigth || par->player->move_left)
	{
		draw_player(par->mini_map, par->player->mini_x,
			par->player->mini_y, 0);
		move(par->map, &par->player, 0.065);
		draw_player(par->mini_map, par->player->mini_x,
			par->player->mini_y, par->player->color);
		draw_floor(par, par->map);
		wall_casting(par, par->player, par->map);
	}
	else if (par->player->left || par->player->rotate_rigth
		|| par->player->rotate_mouse)
	{
		par->player->rotate_mouse = 0;
		(draw_player(par->mini_map, par->player->mini_x,
				par->player->mini_y, 0), rotate(&par->player, PI / 36.0));
		draw_player(par->mini_map, par->player->mini_x,
			par->player->mini_y, par->player->color);
		(draw_floor(par, par->map), wall_casting(par, par->player, par->map));
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->mini_map->img,
		WIDTH - WIDTH_MINI, HEIGHT - HEIGHT_MINI);
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
	{
		par->player->rotate_mouse = 0;
		par->player->left = 1;
	}
	else if (keycode == RIGHT)
	{
		par->player->rotate_mouse = 0;
		par->player->rotate_rigth = 1;
	}
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
	else if (par->player->rotate_mouse == 1)
		par->player->rotate_mouse = 0;
	return (0);
}
