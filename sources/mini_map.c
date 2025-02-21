/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:14:31 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/21 12:23:22 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_img *img, double x, double y, int color)
{
	int		i;
	int		j;
	char	*pixel_color;

	i = -2;
	j = -2;
	while (i < 3)
	{
		j = -2;
		while (j < 3)
		{
			pixel_color = img->addr + ((int)y - j)
				* img->l_len + ((int)x - i) * (img->b_pix / 8);
			if (*(int *)pixel_color != rgb_to_int(128, 128, 128))
			{
				my_mlx_pixel_put(img, (int)x - i, (int)y - j, color);
				j++;
			}
			else
				break ;
		}
		i++;
	}
}

void	draw_walls(t_map *map, double *x, double *y)
{
	int	color;

	color = rgb_to_int(128, 128, 128);
	*y = map->saved_y;
	while (*y < map->saved_y + map->v_mini)
	{
		*x = map->saved_x;
		while (*x < map->saved_x + map->h_mini)
		{
			my_mlx_pixel_put(map->par->mini_map, (int)*x, (int)*y, color);
			(*x)++;
		}
		(*y)++;
	}
}

void	draw_first_map(t_params *par, t_player *player, int i, double y)
{
	int		j;
	double	x;
	int		color;

	j = 0;
	x = 0.0;
	par->map->saved_x = x;
	color = rgb_to_int(255, 0, 0);
	while (j < par->map->length_max)
	{
		if (par->map->map_tab[i][j] && par->map->map_tab[i][j] == '1')
			draw_walls(par->map, &x, &y);
		if (par->map->map_tab[i][j]
			&& ft_strchr("NEWS", par->map->map_tab[i][j]))
		{
			player->mini_x = par->map->saved_x + 0.5 * par->map->h_mini - 1;
			player->mini_y = par->map->saved_y + 0.5 * par->map->v_mini - 1;
			draw_player(par->mini_map, player->mini_x, player->mini_y, color);
		}
		j++;
		x = j * par->map->h_mini;
		par->map->saved_x = x;
		if (par->map->saved_x + par->map->h_mini > WIDTH_MINI)
		par->map->saved_x = 0;
	}
}

void	build_mini_map(t_img *mini_map, t_map *map, t_params *par)
{
	int		i;
	double	y;
	int		w;
	int		h;

	y = 0.0;
	i = 0;
	w = WIDTH - WIDTH_MINI;
	h = HEIGHT - HEIGHT_MINI;
	map->saved_y = y;
	while (i < map->nb_lines)
	{
		draw_first_map(par, par->player, i, y);
		i++;
		y = i * map->v_mini;
		map->saved_y = y;
		if (map->saved_y + map->v_mini > HEIGHT_MINI)
			map->saved_y = 0;
	}
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, mini_map->img, w, h);
}
