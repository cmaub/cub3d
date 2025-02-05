

#include "cub3d.h"

int	is_wall(t_map *map, double new_x, double new_y)
{
	int	grid_x;
	int	grid_y;
	int	ret;

	grid_x = (int)(new_x / (WIDTH / map->length_max));
	grid_y = (int)(new_y / (HEIGHT / map->nb_lines));
	ret = map->map_tab[grid_y][grid_x];
	return (ret);
}

void	move(t_map *map, t_player **player, double distance, int keycode)
{
	double	new_x;
	double	new_y;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos((*player)->angle);
	sin_angle = sin((*player)->angle);
	if (keycode == W)
	{
		new_y = (*player)->pos_y - distance;
		new_x = (*player)->pos_x;
		if (is_wall(map, new_x, new_y) != '1')
			(*player)->pos_y = new_y;
	}
	else if (keycode == S)
	{
		new_y = (*player)->pos_y + distance;
		new_x = (*player)->pos_x;
		if (is_wall(map, new_x, new_y) != '1')
			(*player)->pos_y = new_y;
	}	
	else if (keycode == A)
	{
		new_x = (*player)->pos_x - distance;
		new_y = (*player)->pos_y;
		if (is_wall(map, new_x, new_y) != '1')
			(*player)->pos_x = new_x;
	}
	else if (keycode == D)
	{
		new_x = (*player)->pos_x + distance;
		new_y = (*player)->pos_y;
		if (is_wall(map, new_x, new_y) != '1')
			(*player)->pos_x = new_x;
	}
	else if (keycode == LEFT)
	{
		(*player)->angle -= distance;
		if ((*player)->angle > 2 *PI)
			(*player)->angle = 0;
	}
	else if (keycode == RIGHT)
	{
		(*player)->angle += distance;
		if ((*player)->angle < 0)
			(*player)->angle = 2 * PI;
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
	else if ((keycode == W) || (keycode == S) || (keycode == A) || (keycode == D))
	{
		draw_player(par->img, par->player->pos_x, par->player->pos_y, 0);
		draw_fov(par, par->img, par->map, par->player, 0);
		move(par->map, &par->player, 10, keycode);
		draw_player(par->img, par->player->pos_x, par->player->pos_y, par->player->color);
		draw_fov(par, par->img, par->map, par->player, 255);
	}
	else if ((keycode == LEFT) || (keycode == RIGHT))
	{
		draw_player(par->img, par->player->pos_x, par->player->pos_y, 0);
		draw_fov(par, par->img, par->map, par->player, 0);
		move(par->map, &par->player, 0.2, keycode);
		draw_player(par->img, par->player->pos_x, par->player->pos_y, par->player->color);
		draw_fov(par, par->img, par->map, par->player, 255);
	}
	draw_vertical_grid(par->img, par->map);
	draw_horizontal_grid(par->img, par->map);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img->img, 0, 0);
	return (0);
}
