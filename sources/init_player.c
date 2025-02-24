/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:02:23 by anvander          #+#    #+#             */
/*   Updated: 2025/02/24 17:35:58 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sud(t_player *player, int i, int j)
{
	player->angle = PI / 2;
	player->pos_x = (double)j + 0.5;
	player->pos_y = (double)i + 0.5;
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
	// player->angle = atan2(player->dir_y, player->dir_x);
	dprintf(2, "SUD: (*player)->angle = %f\n", player->angle);
}

void	init_north(t_player *player, int i, int j)
{
	player->angle = 3 * PI / 2;
	player->pos_x = (double)j + 0.5;
	player->pos_y = (double)i + 0.5;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
	dprintf(2, "NORD: (*player)->angle = %f\n", player->angle);
}

void	init_east(t_player *player, int i, int j)
{
	player->angle = 0;
	player->pos_x = (double)j + 0.5;
	player->pos_y = (double)i + 0.5;
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	dprintf(2, "EST: (*player)->angle = %f\n", player->angle);
}

void	init_west(t_player *player, int i, int j)
{
	player->angle = PI;
	player->pos_x = (double)j + 0.5;
	player->pos_y = (double)i + 0.5;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0.0;
	player->plane_y = -0.66;
	dprintf(2, "OUEST: (*player)->angle = %f\n", player->angle);
}

void	init_player_angle(t_player *player, char c, int i, int j)
{
	player->mouse = 0;
	player->move_left = 0;
	player->move_rigth = 0;
	player->move_down = 0;
	player->move_up = 0;
	player->left = 0;
	player->rotate_rigth = 0;
	player->mini_x = 0;
	player->mini_y = 0;
	if (c == 'S')
		init_sud(player, i, j);
	else if (c == 'N')
		init_north(player, i, j);
	else if (c == 'E')
		init_east(player, i, j);
	else if (c == 'W')
		init_west(player, i, j);
}
