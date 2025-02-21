/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:01:17 by anvander          #+#    #+#             */
/*   Updated: 2025/02/21 12:01:56 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_path(t_map *map)
{
	map->wall_no->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_no,
			&map->wall_no->width, &map->wall_no->height);
	map->wall_so->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_so,
			&map->wall_so->width, &map->wall_so->height);
	map->wall_ea->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_ea,
			&map->wall_ea->width, &map->wall_ea->height);
	map->wall_we->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_we,
			&map->wall_we->width, &map->wall_we->height);
	if (!map->wall_no->img || !map->wall_so->img
		|| !map->wall_ea->img || !map->wall_we->img)
	{
		printf("Error\nwith xpm files\n");
		close_window(map->par);
	}	
}

void	get_texture_address(t_map *map)
{
	map->wall_no->addr = mlx_get_data_addr(map->wall_no->img,
			&map->wall_no->b_pix, &map->wall_no->l_len, &map->wall_no->endian);
	map->wall_ea->addr = mlx_get_data_addr(map->wall_ea->img,
			&map->wall_ea->b_pix, &map->wall_ea->l_len, &map->wall_ea->endian);
	map->wall_so->addr = mlx_get_data_addr(map->wall_so->img,
			&map->wall_so->b_pix, &map->wall_so->l_len, &map->wall_so->endian);
	map->wall_we->addr = mlx_get_data_addr(map->wall_we->img,
			&map->wall_we->b_pix, &map->wall_we->l_len, &map->wall_we->endian);
	if (!map->wall_no->addr || !map->wall_so->addr
		|| !map->wall_ea->addr || !map->wall_we->addr)
	{
		printf("Error\nwith address of xpm files\n");
		close_window(map->par);
	}
}

void	init_images(t_params *par, t_img *img, t_img *mini_map)
{
	img->width = WIDTH;
	img->height = HEIGHT;
	mini_map->width = WIDTH_MINI;
	mini_map->height = HEIGHT_MINI;
	img->img = mlx_new_image(par->mlx_ptr, img->width, img->height);
	if (!img->img)
		close_window(par);
	mini_map->img = mlx_new_image(par->mlx_ptr, mini_map->width,
			mini_map->height);
	if (!mini_map)
		close_window(par);
	img->addr = mlx_get_data_addr(img->img, &img->b_pix,
			&img->l_len, &img->endian);
	mini_map->addr = mlx_get_data_addr(mini_map->img, &mini_map->b_pix,
			&mini_map->l_len, &mini_map->endian);
}
