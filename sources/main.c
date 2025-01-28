/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:59:12 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/28 12:27:08 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy(t_params *par)
{
	if (par->img.img)
		mlx_destroy_image(par->mlx_ptr, par->img.img);
	if (par->win_ptr)
		mlx_destroy_window(par->mlx_ptr, par->win_ptr);
	if (par->mlx_ptr)
	{
		mlx_destroy_display(par->mlx_ptr);
		free(par->mlx_ptr);
	}
	// if (par)
	// 	free_params(par);
	exit(0);
}

void    init_structs(t_params *par)
{
    t_img *img;

    img = par->img;
    par->mlx_ptr = NULL;
    par->win_ptr = NULL;
    par->mlx_ptr = mlx_init();
    if (!par->mlx_ptr)
       destroy(par);
    par->win_ptr = mlx_new_window(par->mlx_ptr, WIDTH, LENGTH, "cub3d");
    if (!par->win_ptr)
        destroy(par); // fonction destroy
	img->width = WIDTH;
	img->length = LENGTH;
    img->img = mlx_new_image(par->mlx_ptr, img->width, img->length);
    if (!img->img)
        destroy(par);
    img->addr = mlx_get_data_addr(img->img, &img->b_pix, &img->l_len, &img->endian);
    
}

int main(void)
{
    t_params par;
    
    init_structs(&par);
}