/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:55:04 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/31 16:46:19 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# define TRUE 1
# define FALSE 0

# define LENGTH 800
# define WIDTH 1100

# include "mlx.h"
# include <errno.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include <limits.h>//
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		b_pix;
	int		l_len;
	int		endian;
	int		width;
	int		length;
}	t_img;

typedef struct s_player
{
	double 	pos_x;
	double 	pos_y;
	int		color;
	char	orient;
}	t_player;

typedef struct s_map
{
	int			length_max;
	int			nb_lines;
	char 		**parse_file;
	char		**map_tab;
	int			map_x;
	int			map_y;
	int			map_s;
	int			color;
	t_img		floor;
	t_img		ceiling;
	t_img		wall_no;
	t_img		wall_so;
	t_img		wall_ea;
	t_img		wall_we;
	int			rgb_floor;
	int			rgb_ceil;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	t_player	player;
}	t_map;

typedef struct s_params
{
	void		*mlx_ptr;
	void		*win_ptr;
	// t_map	*map;
	t_img		img;
	t_player	player;
	t_map		*map;
}	t_params;



/* Parsing */
int	check_av(t_map *map, char **str, int count);
int	check_map(char **str, t_map *map, int i);
int	check_color_params(char *str, int *rgb);
int	rgb_to_int(int r, int g, int b);
void	replace_spaces(char **str, t_map *map, int index);
void	print_map(char **str);
void	print_tab(char **str, t_map *map);


/* Init */
void	count_alloc(t_map *map, char *file);
void    init_structs(t_params *par);
void	init_t_map(t_params *par);
void	destroy(t_params *par);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    draw_map(t_img *img, t_map *map);

#endif