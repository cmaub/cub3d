/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:55:43 by anvander          #+#    #+#             */
/*   Updated: 2025/02/20 15:56:18 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_map *map, t_player **player, double dist)
{
	double	new_mini_x;
	double	new_mini_y;
	double	new_x;
	double	new_y;

	new_x = (*player)->pos_x + cos((*player)->angle) * dist;
	new_y = (*player)->pos_y + sin((*player)->angle) * dist;
	new_mini_x = (*player)->mini_pos_x + cos((*player)->angle) * dist * map->unit_h_mini;
	new_mini_y = (*player)->mini_pos_y + sin((*player)->angle) * dist * map->unit_v_mini;
	if (!check_hit_and_update(map, new_x, new_y, player))
		return ;
	(*player)->mini_pos_x = new_mini_x;
	(*player)->mini_pos_y = new_mini_y;
}

void	move_down(t_map *map, t_player **player, double dist)
{
	double	new_mini_x;
	double	new_mini_y;
	double	new_x;
	double	new_y;

	new_x = (*player)->pos_x - cos((*player)->angle) * dist;
	new_y = (*player)->pos_y - sin((*player)->angle) * dist;
	new_mini_x = (*player)->mini_pos_x - cos((*player)->angle) * dist * map->unit_h_mini;
	new_mini_y = (*player)->mini_pos_y - sin((*player)->angle) * dist * map->unit_v_mini;
	if (!check_hit_and_update(map, new_x, new_y, player))
		return ;
	(*player)->mini_pos_x = new_mini_x;
	(*player)->mini_pos_y = new_mini_y;
}

void	move_left(t_map *map, t_player **player, double dist)
{
	double	new_mini_x;
	double	new_mini_y;
	double	new_x;
	double	new_y;

	new_x = (*player)->pos_x + sin((*player)->angle) * dist;
	new_y = (*player)->pos_y - cos((*player)->angle) * dist;
	new_mini_x = (*player)->mini_pos_x + sin((*player)->angle) * dist * map->unit_h_mini;
	new_mini_y = (*player)->mini_pos_y - cos((*player)->angle) * dist * map->unit_v_mini;
	if (!check_hit_and_update(map, new_x, new_y, player))
		return ;
	(*player)->mini_pos_x = new_mini_x;
	(*player)->mini_pos_y = new_mini_y;
}

void	move_rigth(t_map *map, t_player **player, double dist)
{
	double	new_mini_x;
	double	new_mini_y;
	double	new_x;
	double	new_y;

	new_x = (*player)->pos_x - sin((*player)->angle) * dist;
	new_y = (*player)->pos_y + cos((*player)->angle) * dist;
	new_mini_x = (*player)->mini_pos_x - sin((*player)->angle) * dist  * map->unit_h_mini;
	new_mini_y = (*player)->mini_pos_y + cos((*player)->angle) * dist * map->unit_v_mini;
	if (!check_hit_and_update(map, new_x, new_y, player))
		return ;
	(*player)->mini_pos_x = new_mini_x;
	(*player)->mini_pos_y = new_mini_y;
}

void	move(t_map *map, t_player **player, double dist)
{
	(*player)->angle = atan2((*player)->dir_y, (*player)->dir_x);
	if ((*player)->angle < 0)
		(*player)->angle += 2 * PI;
	if ((*player)->move_up)
		move_up(map, player, dist);
	else if ((*player)->move_down)
		move_down(map, player, dist);
	else if ((*player)->move_left)
		move_left(map, player, dist);
	else if ((*player)->move_rigth)
		move_rigth(map, player, dist);
}
