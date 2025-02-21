/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:56:27 by anvander          #+#    #+#             */
/*   Updated: 2025/02/21 16:36:44 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	left(t_player **p, double *o_dir_x, double *o_plane_x, double dist)
{
	double	speed;

	speed = -dist / 4;
	(*p)->angle -= dist;
	if ((*p)->angle < 0)
		(*p)->angle += 2 * PI;
	*o_dir_x = (*p)->dir_x;
	(*p)->dir_x = (*p)->dir_x * cos(speed) - (*p)->dir_y * sin(speed);
	(*p)->dir_y = (*o_dir_x) * sin(speed) + (*p)->dir_y * cos(speed);
	(*o_plane_x) = (*p)->plane_x;
	(*p)->plane_x = (*p)->plane_x * cos(speed) - (*p)->plane_y * sin(speed);
	(*p)->plane_y = (*o_plane_x) * sin(speed) + (*p)->plane_y * cos(speed);
}

void	right(t_player **p, double *o_dir_x, double *o_plane_x, double dist)
{
	double	speed;

	speed = dist / 4;
	(*p)->angle += dist;
	if ((*p)->angle > 2 * PI)
		(*p)->angle -= 2 * PI;
	*o_dir_x = (*p)->dir_x;
	(*p)->dir_x = (*p)->dir_x * cos(speed) - (*p)->dir_y * sin(speed);
	(*p)->dir_y = *o_dir_x * sin(speed) + (*p)->dir_y * cos(speed);
	*o_plane_x = (*p)->plane_x;
	(*p)->plane_x = (*p)->plane_x * cos(speed) - (*p)->plane_y * sin(speed);
	(*p)->plane_y = *o_plane_x * sin(speed) + (*p)->plane_y * cos(speed);
}

void	rotate(t_player **player, double dist)
{
	double	o_dir_x;
	double	o_plane_x;

	o_dir_x = 0;
	o_plane_x = 0;
	if ((*player)->left)
		left(player, &o_dir_x, &o_plane_x, dist);
	else if ((*player)->rotate_rigth)
		right(player, &o_dir_x, &o_plane_x, dist);
}

void	rotate_mouse(t_player **player, double dist, double delta_x)
{
	double	o_dir_x;
	double	o_plane_x;

	o_dir_x = 0;
	o_plane_x = 0;
	if (delta_x < 0)
		left(player, &o_dir_x, &o_plane_x, dist);
	else if (delta_x > 0)
		right(player, &o_dir_x, &o_plane_x, dist);
}
