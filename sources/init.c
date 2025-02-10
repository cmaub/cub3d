/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:30:57 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/10 17:31:27 by anvander         ###   ########.fr       */
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
		*angle = PI / 2;
	else if (c == 'N')
		*angle = 3 * PI / 2;
	else if (c == 'E')
		*angle = 0;
	else if (c == 'W')
		*angle = PI;
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

/*
TO DO: clean tout en cas d'erreur
*/
void	get_texture_path(t_map *map)
{
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
	dprintf(2, "map->par->mlx_ptr = %p\n", map->par->mlx_ptr);
	dprintf(2, "map->path_no = %s\n", map->path_no);
	dprintf(2, "map->wall_no->width = %d\n", map->wall_no->width);
	dprintf(2, "map->wall_no->height = %d\n", map->wall_no->height);
	map->wall_no->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_no,
				&map->wall_no->width, &map->wall_no->height);
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
	map->wall_so->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_so,
				&map->wall_so->width, &map->wall_so->height);
	map->wall_ea->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_ea,
				&map->wall_ea->width, &map->wall_ea->height);
	map->wall_we->img = mlx_xpm_file_to_image(map->par->mlx_ptr, map->path_we,
				&map->wall_we->width, &map->wall_we->height);
	if (!map->wall_no->img || !map->wall_so->img || !map->wall_ea->img || !map->wall_we->img)
		printf("error\n");			
}

void	get_texture_address(t_map *map)
{
	map->wall_no->addr = mlx_get_data_addr(map->wall_no->img, &map->wall_no->b_pix, 
					&map->wall_no->l_len, &map->wall_no->endian);
	map->wall_ea->addr = mlx_get_data_addr(map->wall_ea->img, &map->wall_ea->b_pix, 
					&map->wall_ea->l_len, &map->wall_ea->endian);
	map->wall_so->addr = mlx_get_data_addr(map->wall_so->img, &map->wall_so->b_pix, 
					&map->wall_so->l_len, &map->wall_so->endian);
	map->wall_we->addr = mlx_get_data_addr(map->wall_we->img, &map->wall_we->b_pix, 
					&map->wall_we->l_len, &map->wall_we->endian);					
}

void    init_structs(t_params *par)
{
    t_img	*img;
	t_img	*mini_map;

    par->img = try_malloc(sizeof(t_img));
	par->map->wall_no = try_malloc(sizeof(t_img));
	par->map->wall_so = try_malloc(sizeof(t_img));
	par->map->wall_ea = try_malloc(sizeof(t_img));
	par->map->wall_we = try_malloc(sizeof(t_img));
	par->mini_map = try_malloc(sizeof(t_img));
	par->player = try_malloc(sizeof(t_player));
	par->ray = try_malloc(sizeof(t_ray));
	par->img->player = par->player;
	img = par->img;
	mini_map = par->mini_map;
    par->mlx_ptr = NULL;
    par->win_ptr = NULL;
    par->mlx_ptr = mlx_init();
	par->map->height = 0;
	par->map->par = par;
	// par->map->wall_no->width = 64;
	// par->map->wall_no->height = 64;
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
	get_texture_path(par->map);
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
	get_texture_address(par->map);
	dprintf(2, "%s, %d\n", __FILE__, __LINE__);
    if (!par->mlx_ptr)
       destroy(par);
    par->win_ptr = mlx_new_window(par->mlx_ptr, WIDTH, HEIGHT, "cub3d");
    if (!par->win_ptr)
        destroy(par);
    else
    {
	    img->width = WIDTH;
	    img->height = HEIGHT;
		mini_map->width = WIDTH_MINI;
		mini_map->height = HEIGHT_MINI;
        img->img = mlx_new_image(par->mlx_ptr, img->width, img->height);
		mini_map->img = mlx_new_image(par->mlx_ptr, mini_map->width, mini_map->height);
        if (!img->img)
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
