#include "cub3d.h"

void	move(t_player **player, double distance, int keycode)
{
	if (keycode == W)
	{
		dprintf(2, "keycode identifie W\n");
		(*player)->pos_y -= distance;
	}
	else if (keycode == S)
		(*player)->pos_y += distance;
	else if (keycode == A)
		(*player)->pos_x -= distance;
	else if (keycode == D)
	{
		dprintf(2, "keycode identifie D\n");
		(*player)->pos_x += distance;
	}
}

int	close_window(t_params *par)
{
	if (!par)
	{
		exit(1);
		return (0);
	}
	if (par->img)
		mlx_destroy_image(par->mlx_ptr, par->img->img);
	if (par->win_ptr)
		mlx_destroy_window(par->mlx_ptr, par->win_ptr);
	if (par->mlx_ptr)
	{
		mlx_destroy_display(par->mlx_ptr);
		free(par->mlx_ptr);
		free(par);
	}
	exit(1);
	return (0);
}

int	key_event(int keycode, t_params *par)
{
    if (keycode == KEY_ESC)
        close_window(par);
	else if ((keycode == W) || (keycode == S) || (keycode == 25) || (keycode == D))
	{
		dprintf(2, "keycode pressed\n");
		move(&par->player, 50, keycode);
	}
	mlx_destroy_image(par->mlx_ptr, par->img->img);
	par->img->img = mlx_new_image(par->mlx_ptr, WIDTH, HEIGHT);
	par->img->addr = mlx_get_data_addr(par->img->img, &par->img->b_pix, &par->img->l_len, &par->img->endian);
	draw_map(par->img, par->map);
	draw_player(par->img, par->map, par->player, par->player->pos_x, par->player->pos_y);
	draw_vertical_grid(par->img, par->map);
	draw_horizontal_grid(par->img, par->map);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
	return (0);
}
