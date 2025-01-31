/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:33:25 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/31 17:33:47 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->length)
		return ;
	dst = img->addr + (y * img->l_len + x * (img->b_pix / 8));
	*(unsigned int *)dst = color;
}

void    draw_map(t_img *img, t_map *map)
{
    int	j;
	int	i;
	double	x;
	double	y;
	double	saved_x;
	double	saved_y;
	
	i = 0;
	y = 0.0;
	x = 0.0;
	saved_x = x;
	saved_y = y;
	while (i <= map->nb_lines)
	{
		j = 0;
		while (j < map->length_max)
		{
			dprintf(2, "map->map_tab[%d][%d] = %c\n", i, j, map->map_tab[i][j]);
			if (map->map_tab[i][j] == '1')
			{
				// y += i * 64;
				dprintf(2, "saved_x = %f, saved_y = %f\n", saved_x, saved_y);
				y = saved_y;
				while (y < saved_y + 64)
				{
					x = saved_x;
					// x += j * 64;
					while (x < saved_x + 64)
					{
						dprintf(2, "coucou\n");
						my_mlx_pixel_put(img, x, y, 255);
						x++;
					}
					y++;
				}
				x = j * 64;
				saved_x = x;
				y = i *64;
				saved_y = y;
			}
			// x0 = x * map->map_s;
			// y0 = y * map->map_s;
			j++;
		}
		i++;
	}
}

