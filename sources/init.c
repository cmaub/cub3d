/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:30:57 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/04 17:29:53 by anvander         ###   ########.fr       */
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

void	init_t_map(t_params *par)
{
	par->map = try_malloc(sizeof(t_map));
	par->map->length_max = 0;
	par->map->nb_lines = 0;
	// dprintf(2, "adresse nb_lines %p\n", &map->nb_lines);
	// char **parse_file;
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
    t_img *img;

    par->img = try_malloc(sizeof(t_img));
	par->player = try_malloc(sizeof(t_player));
	par->img->player = par->player;
	img = par->img;
    par->mlx_ptr = NULL;
    par->win_ptr = NULL;
    par->mlx_ptr = mlx_init();
    if (!par->mlx_ptr)
       destroy(par);
    par->win_ptr = mlx_new_window(par->mlx_ptr, WIDTH, HEIGHT, "cub3d");
    if (!par->win_ptr)
        destroy(par);
    else
    {
	    img->width = WIDTH;
	    img->height = HEIGHT;
        img->img = mlx_new_image(par->mlx_ptr, img->width, img->height);
        if (!img->img)
            destroy(par);
        img->addr = mlx_get_data_addr(img->img, &img->b_pix, &img->l_len, &img->endian);
    }
	par->player->pos_x = 500; // 
	par->player->pos_y = 600; // 
    par->player->color = rgb_to_int(255, 0, 0);
    par->player->pos_x = 0;
    par->player->pos_y = 0;
    // par->map.map_x = 4;
    // par->map.map_y = 4;
    // par->map.map_s = 64;
	// // int **map;
    // int parse_file[4][4] = {{1, 1, 1, 1},{1, 0, 0, 1},{1, 0, 0, 1},{1, 0, 0, 1}};	
	// // map[1][4] = {1, 0, 0, 1};
	// // map[2][4] = {1, 0, 0, 1};
	// // map[3][4] = {1, 1, 1, 1};
	// par->map.map = (int **)parse_file;
	// draw_map(img, &par->map);
    
}
