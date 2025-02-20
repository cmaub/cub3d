/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:56:27 by anvander          #+#    #+#             */
/*   Updated: 2025/02/20 16:50:37 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	left(t_player **play, double *o_dir_x, double *o_plane_x, double dist)
{
	(*play)->angle -= dist;
	if ((*play)->angle < 0)
		(*play)->angle += 2 * PI;
	*o_dir_x = (*play)->dir_x;
	(*play)->dir_x = (*play)->dir_x * cos(-dist / 4) - (*play)->dir_y * sin(-dist / 4); //creer variables pur que se soit propre
	(*play)->dir_y = (*o_dir_x) * sin(-dist / 4) + (*play)->dir_y * cos(-dist / 4);
	(*o_plane_x) = (*play)->plane_x;
	(*play)->plane_x = (*play)->plane_x * cos(-dist / 4) - (*play)->plane_y * sin(-dist / 4);
	(*play)->plane_y = (*o_plane_x) * sin(-dist / 4) + (*play)->plane_y * cos(-dist / 4);
}

void	right(t_player **play, double *o_dir_x, double *o_plane_x, double dist)
{
	(*play)->angle += dist;
	if ((*play)->angle > 2 * PI)
		(*play)->angle -= 2 * PI;
	*o_dir_x = (*play)->dir_x;
	(*play)->dir_x = (*play)->dir_x * cos(dist / 4) - (*play)->dir_y * sin(dist / 4);
	(*play)->dir_y = *o_dir_x * sin(dist / 4) + (*play)->dir_y * cos(dist / 4);
	*o_plane_x = (*play)->plane_x;
	(*play)->plane_x = (*play)->plane_x * cos(dist / 4) - (*play)->plane_y * sin(dist / 4);
	(*play)->plane_y = *o_plane_x * sin(dist / 4) + (*play)->plane_y * cos(dist / 4);
}

void	rotate(t_player **play, double dist)
{
	double	o_dir_x;
	double	o_plane_x;

	o_dir_x = 0;
	o_plane_x = 0;
	if ((*play)->left)
		left(play, &o_dir_x, &o_plane_x, dist);
	else if ((*play)->rotate_rigth)
		right(play, &o_dir_x, &o_plane_x, dist);
}
