/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:59:12 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/29 12:46:51 by cmaubert         ###   ########.fr       */
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

    img = &par->img;
    par->mlx_ptr = NULL;
    par->win_ptr = NULL;
    par->mlx_ptr = mlx_init();
    if (!par->mlx_ptr)
       destroy(par);
    par->win_ptr = mlx_new_window(par->mlx_ptr, WIDTH, LENGTH, "cub3d");
    if (!par->win_ptr)
        destroy(par);
    else
    {
	    img->width = WIDTH;
	    img->length = LENGTH;
        img->img = mlx_new_image(par->mlx_ptr, img->width, img->length);
        if (!img->img)
            destroy(par);
        img->addr = mlx_get_data_addr(img->img, &img->b_pix, &img->l_len, &img->endian);
    }
    par->player.color = rgb_to_int(255, 255, 255);
    par->player.pos_x = 300;
    par->player.pos_y = 300;
    
}

int main(void)
{
    t_params par;
    
    init_structs(&par);
    my_mlx_pixel_put(&par.img, par.player.pos_x, par.player.pos_y, par.player.color);
    mlx_put_image_to_window(par.mlx_ptr, par.win_ptr, par.img.img, 0, 0);
    mlx_loop(par.mlx_ptr);
    return (0);
}