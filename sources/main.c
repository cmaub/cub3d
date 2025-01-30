/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:59:12 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/30 17:28:17 by anvander         ###   ########.fr       */
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

void	print_tab(char **str, t_map *map)
{
	int	i;

	printf("map->path_no = %s\n", map->path_no);
	printf("map->path_so = %s\n", map->path_so);
	printf("map->path_we = %s\n", map->path_we);
	printf("map->path_ea = %s\n", map->path_ea);
	printf("map->rgb_floor = %d\n", map->rgb_floor);
	printf("map->rgb_ceil = %d\n", map->rgb_ceil);
	i = 0;
	while (str[i])
	{
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
}

void	print_map(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("map[%d] = %s\n", i, str[i]);
		i++;
	}
}

void	replace_spaces(char **str, t_map *map, int index)
{
	int	i;
	int	j;
	(void)index;

	i = 0;
	// map->map_tab = try_malloc(sizeof(char *))
	while (str[i] && i <= map->nb_lines)
	{
		j = 0;
		while (str[i][j] && j < map->length_max)
		{
			if (str[i][j] == ' ')
				str[i][j] = '1';
			j++;
		}
		while (j < map->length_max)
		{
			if (str[i][j] == '\0')
				str[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	all_path_filled(t_map *map)
{
	if (!map->path_no || !map->path_so || !map->path_ea || !map->path_we || map->rgb_floor == -1|| map->rgb_ceil == -1)
		return (FALSE);
	return (TRUE);
}

int	is_color_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	if (ft_strlen(str) > 3)
		return (FALSE);
	return (TRUE);
}

int	check_color_params(char *str, int *rgb)
{
	char **params;
	int	i;
	int	nb;
	
	str += 2;
	i = 0;
	params = ft_split(str, ',');
	if (!params)
		return (printf("line %d\n", __LINE__),FALSE);
	while (params[i])
	{
		if (!is_color_valid(params[i]))
			return (FALSE);
		nb = ft_atoi(params[i]);
		if (nb < 0 || nb > 255)
			return (FALSE);
		i++;
	}
	if (i != 3)
		return (printf("line %d\n", __LINE__),FALSE);
	(*rgb) = rgb_to_int(ft_atoi(params[0]), ft_atoi(params[1]), ft_atoi(params[2]));
	return (TRUE);
}

int	check_av(t_map *map, char **str, int count)
{
	int	i;
	(void)count;

	i = 0;
	
	while (str[i] && !str[i][0])
		i++;
	str += i;
	while (str[i] && i < count)
	{
		// printf("str[%d] = %s\n", i, str[i]);
		if (!str[i][0])
		{
			if (all_path_filled(map))
				break;
			i++;
		}
		if (!ft_strncmp(str[i], "NO", 2))
		{
			if (map->path_no)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_no = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "SO", 2))
		{
			if (map->path_so)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_so = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "WE", 2))
		{
			if (map->path_we)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_we = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "EA", 2))
		{
			if (map->path_ea)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			map->path_ea = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "F ", 2))
		{
			if (map->rgb_floor != -1)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			if (!check_color_params(str[i], &map->rgb_floor))
				return (printf("error\n"), FALSE); //TODO
			
		}
		if (!ft_strncmp(str[i], "C ", 2))
		{
			if (map->rgb_ceil != -1)
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			if (!check_color_params(str[i], &map->rgb_ceil))
				return (printf("error\n"), FALSE);
		}
		i++;
	}
	if (!all_path_filled(map))
	{
		//free
		printf("error line %d\n", __LINE__);
		return (FALSE);
	}
	while (!str[i][0])
			i++;
	str += i;
	check_map(str, map, i);
	return (TRUE);
}

int	check_map(char **str, t_map *map, int index)
{
	int	i;
	int	j;
	int	len_i;
	int	count_j;
	int	flag;
	int save_index;
	
	i = 0;
	len_i = 0;
	count_j = 0;
	flag = 0;
	save_index = index;
	map->length_max = 0;
	while (str[i] && index < map->nb_lines)
	{
		// printf("str[%d] = %s\n", i, str[i]);
		j = 0;
		len_i = ft_strlen(str[i]);
		if (len_i > map->length_max)
			map->length_max = len_i;
		while (str[i][j] && j < len_i)
		{
			if (i == 0 || j == 0 || j == len_i - 1|| !str[i + 1])
			{
				if ((str[i][j] !=  '1' && str[i][j] != ' '))
				{
					printf("error line %d\n", __LINE__);; //TODO
					return (FALSE);
				}
				if (str[i][j] == ' ')
				{
					if (j != 0)
					{
						if (str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
					if (j != len_i)
					{
						if (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
					if (i != 0)
					{
						if (str[i - 1][j] && !ft_strchr("1 ", str[i - 1][j]))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
					if (str[i + 1])
					{
						if (str[i + 1][j] && !ft_strchr("1 ", str[i + 1][j]))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
				}
			}
			else 
			{
				if (!ft_strchr("01NEWS ", str[i][j]))
				{
					printf("error line %d\n", __LINE__);; //TODO
					return (FALSE);
				}
				if (str[i][j] == ' ')
				{
					if (j < (int)ft_strlen(str[i - 1]))
					{	
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
							|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
							|| (str[i - 1][j] && !ft_strchr("1 ", str[i - 1][j])))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
					else
					{
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1])))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
					if (j < (int)ft_strlen(str[i + 1]))
					{	
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
							|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
							|| (str[i + 1][j] && !ft_strchr("1 ", str[i + 1][j])))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
					else
					{
						if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1])))
						{
							printf("error line %d\n", __LINE__);; //TODO
							return (FALSE);
						}
					}
				}
				if (ft_strchr("NEWS", str[i][j]))
				{
					map->player.orient = str[i][j];
					flag++;
				}
			}
			j++;
		}
		if (index <  map->nb_lines && j == 0)
		{
			printf("error, ligne vide\n");
			return (FALSE);
		}
		i++;
		index += 1;
	}
	map->nb_lines = i - 1;
	if (flag != 1)
	{
		printf("error line %d\n", __LINE__);; //TODO
		return (FALSE);
	}
	replace_spaces(str, map, save_index);
	map->map_tab = str;
	print_map(str);
	return (TRUE);
}

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

int main(int ac, char **av)
{
    t_params *par;
	int	fd;
	char	*str;
	int	i;
	(void)ac;

	par = try_malloc(sizeof(t_params));
	init_t_map(par);
	// revoir verification exit
	count_alloc(par->map, av[1]);
	fd = open(av[1], R_OK);
	i = 0;
	str = NULL;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if(str[ft_strlen(str) -1] == '\n')
			str[ft_strlen(str) -1] = '\0';
		par->map->parse_file[i] = try_malloc(sizeof(char) * par->map->length_max + 1);
		ft_strlcpy(par->map->parse_file[i], str, par->map->length_max);
		free(str);
		i++;
	}
	par->map->parse_file[i] = "\0";
	if (!check_av(par->map, par->map->parse_file, i))
		return (1);
	// print_tab(par->map->map_tab, par->map);
    init_structs(par);
    my_mlx_pixel_put(&par->img, par->player.pos_x, par->player.pos_y, par->player.color);
	draw_map(&par->img, par->map);
    mlx_put_image_to_window(par->mlx_ptr, par->win_ptr, par->img.img, 0, 0);
    mlx_loop(par->mlx_ptr);
    return (0);
}