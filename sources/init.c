/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:30:57 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/06 18:32:54 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_alloc(t_map *map, char *file)
{
	int	fd;
	char *str;
	
	fd = open(file, R_OK);
	
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break;
		map->nb_lines++;
		if ((int)ft_strlen(str) > map->length_max)
			map->length_max = (int)ft_strlen(str);
		free(str);
	}
	close(fd);
	map->parse_file = malloc(sizeof(char *) * (map->nb_lines * map->length_max + 1));
	
}

/*
cf unit circle in computer graphics.
*/
void	init_player_angle(double *angle, char c)
{
	if (c == 'S')
		*angle = 0;
	else if (c == 'N')
		*angle = PI;
	else if (c == 'E')
		*angle = 3 * PI / 2;
	else if (c == 'W')
		*angle = PI / 2;
	dprintf(2, "angle = %f\n", *angle);
}

void	init_t_map(t_params *par)
{
	par->map = try_malloc(sizeof(t_map));
	par->map->length_max = 0;
	par->map->nb_lines = 0;
	par->map->map_x = 0;
	par->map->map_y = 0;
	par->map->map_s = 0;
	par->map->color = 0;
	// map->floor = try_malloc(sizeof(t_img));
	// map->ceiling = try_malloc(sizeof(t_img));
	// map->wall_no = try_malloc(sizeof(t_img));
	// map->wall_so = try_malloc(sizeof(t_img));
	// map->wall_ea = try_malloc(sizeof(t_img));
	// map->wall_we = try_malloc(sizeof(t_img));
	par->map->rgb_floor = -1;
	par->map->rgb_ceil = -1;
	par->map->path_no = NULL;
	par->map->path_so = NULL;
	par->map->path_ea = NULL;
	par->map->path_we = NULL;
	
}

void    init_structs(t_params *par)
{
    t_img	*img;
	t_img	*mini_map;

    par->img = try_malloc(sizeof(t_img));
	par->mini_map = try_malloc(sizeof(t_img));
	par->player = try_malloc(sizeof(t_player));
	par->ray = try_malloc(sizeof(t_ray));
	par->img->player = par->player;
	img = par->img;
	mini_map = par->mini_map;
    par->mlx_ptr = NULL;
    par->win_ptr = NULL;
    par->mlx_ptr = mlx_init();
    if (!par->mlx_ptr)
       destroy(par);
    par->win_ptr = mlx_new_window(par->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
    if (!par->win_ptr)
        destroy(par);
    else
    {
	    img->width = WIDTH;
	    img->height = HEIGHT;
		dprintf(2, "%s, %d\n", __FILE__, __LINE__);
        img->img = mlx_new_image(par->mlx_ptr, img->width, img->height);
		mini_map->img = mlx_new_image(par->mlx_ptr, 100, 100);
        if (!img->img || !mini_map->img)
            destroy(par);
        img->addr = mlx_get_data_addr(img->img, &img->b_pix, &img->l_len, &img->endian);
		mini_map->addr = mlx_get_data_addr(mini_map->img, &mini_map->b_pix, &mini_map->l_len, &mini_map->endian);
    }
	par->player->pos_x = 0; // 
	par->player->pos_y = 0; // 
    par->player->color = rgb_to_int(255, 0, 0);
	par->player->fov = FOV;
	par->player->angle = par->map->player.angle;
}
