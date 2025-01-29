/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:59:12 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/29 18:28:17 by anvander         ###   ########.fr       */
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

// void    draw_map(t_img *img, t_map *map)
// {
//     int	x;
// 	int	y;
// 	// int	x0;
// 	// int	y0;
	
// 	y = 0;
// 	while (y < map->map_y)
// 	{
// 		x = 0;
// 		while (x < map->map_x)
// 		{
// 			if (map[y * map->map_x + x] == 1)
// 				my_mlx_pixel_put(img, x, y, map->color);
// 			// x0 = x * map->map_s;
// 			// y0 = y * map->map_s;
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
    // int map_tab[4][4] = {{1, 1, 1, 1},{1, 0, 0, 1},{1, 0, 0, 1},{1, 0, 0, 1}};	
	// // map[1][4] = {1, 0, 0, 1};
	// // map[2][4] = {1, 0, 0, 1};
	// // map[3][4] = {1, 1, 1, 1};
	// par->map.map = (int **)map_tab;
	// draw_map(img, &par->map);
    
}

void	print_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
}

void	replace_spaces(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] && j < (int)ft_strlen(str[i]))
		{
			if (str[i][j] == ' ')
				str[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	check_av(char **str, char **texture, int count)
{
	int	i;

	i = 0;
	texture = try_malloc(sizeof(char *) * 6);
	while (str[i] && i < count)
	{
		if (!str[i][0])
		{
			dprintf(2, "str[%d] = %s\n", i, str[i]);
			i++;
		}
		if (!ft_strncmp(str[i], "NO", 2))
		{
			if (texture[0])
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			texture[0] = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "SO", 2))
		{
			if (texture[1])
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			texture[1] = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "WE", 2))
		{
			if (texture[2])
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			texture[2] = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "EA", 2))
		{
			if (texture[3])
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			texture[3] = ft_substr(str[i], 3, ft_strlen(str[i]) - 3);
		}
		if (!ft_strncmp(str[i], "F ", 2))
		{
			if (texture[4])
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			texture[4] = ft_substr(str[i], 2, ft_strlen(str[i]) - 2);
		}
		if (!ft_strncmp(str[i], "C ", 2))
		{
			if (texture[5])
			{
				printf("error line %d\n", __LINE__);
				return (FALSE);
			}
			texture[5] = ft_substr(str[i], 2, ft_strlen(str[i]) - 2);
		}
		i++;
	}
	i = 0;
	while (i < 6)
	{
		dprintf(2, "texture[%d] %s\n", i, texture[i]);
		if (!texture[i])
		{
			printf("error line %d\n", __LINE__);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	check_map(char **str)
{
	int	i;
	int	j;
	int	len_i;
	int	count_j;
	int	flag;
	
	i = 0;
	len_i = 0;
	count_j = 0;
	flag = 0;
	while (str[i])
	{
		j = 0;
		len_i = ft_strlen(str[i]);
		while (str[i][j] && j < len_i)
		{
			if (i == 0 || j == 0 || j == len_i - 1|| !str[i + 1])
			{
				if ((str[i][j] !=  '1' && str[i][j] != ' '))
				{
					printf("error\n"); //TODO
					return (FALSE);
				}
				if (str[i][j] == ' ')
				{
					if (j != 0)
					{
						if (str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						{
							printf("error\n"); //TODO
							return (FALSE);
						}
					}
					if (j != len_i)
					{
						if (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
						{
							printf("error\n"); //TODO
							return (FALSE);
						}
					}
					if (i != 0)
					{
						if (str[i - 1][j] && !ft_strchr("1 ", str[i - 1][j]))
						{
							printf("error\n"); //TODO
							return (FALSE);
						}
					}
					if (str[i + 1])
					{
						if (str[i + 1][j] && !ft_strchr("1 ", str[i + 1][j]))
						{
							printf("error\n"); //TODO
							return (FALSE);
						}
					}
				}
			}
			else 
			{
				if (!ft_strchr("01NEWS ", str[i][j]))
				{
					printf("error\n"); //TODO
					return (FALSE);
				}
				if (str[i][j] == ' ')
				{
					if ((str[i][j - 1] && !ft_strchr("1 ", str[i][j - 1]))
						|| (str[i][j + 1] && !ft_strchr("1 ", str[i][j + 1]))
						|| (str[i - 1][j] && !ft_strchr("1 ", str[i - 1][j]))
						|| (str[i + 1][j] && !ft_strchr("1 ", str[i + 1][j])))
					{
						printf("error\n"); //TODO
						return (FALSE);
					}
				}
				if (ft_strchr("NEWS", str[i][j]))
					flag++;
			}
			j++;
		}
		if (j == 0)
		{
			printf("error, ligne vide\n");
			return (FALSE);
		}
		i++;
	}
	if (flag != 1)
	{
		printf("error\n"); //TODO
		return (FALSE);
	}
	replace_spaces(str);
	// print_tab(str);
	return (TRUE);
}

int main(int ac, char **av)
{
    t_params par;
	int	fd;
	char	*str;
	int	i;
	(void)ac;

	fd = open(av[1], R_OK);
	i = 0;
	str = NULL;
	// par = malloc(sizeof(t_params));
	par.map = malloc(sizeof(t_map));
	if (!par.map)
		return (FALSE);
	par.map->map_tab = malloc(sizeof(char *) * 10);
	if (!par.map->map_tab)
		return (FALSE); //fonction qui free
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if(str[ft_strlen(str) -1] == '\n')
			str[ft_strlen(str) -1] = '\0';
		par.map->map_tab[i] = ft_strdup(str);
		free(str);
		i++;
	}
	if (!check_av(par.map->map_tab, par.map->texture, i))
		return (1);
	print_tab(par.map->map_tab);
    init_structs(&par);
    my_mlx_pixel_put(&par.img, par.player.pos_x, par.player.pos_y, par.player.color);
    mlx_put_image_to_window(par.mlx_ptr, par.win_ptr, par.img.img, 0, 0);
    mlx_loop(par.mlx_ptr);
    return (0);
}