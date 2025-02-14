/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:55:04 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/14 10:42:14 by anvander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# define TRUE 1
# define FALSE 0

# define HEIGHT_MINI 200
# define WIDTH_MINI 320
# define HEIGHT 832
# define WIDTH 1280
# define FOV 66
# define PI 3.14159265359

# define W 119
# define S 115
# define A 97
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define KEY_ESC 65307

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

typedef struct s_params t_params;

typedef struct s_player
{
	double 	pos_x;
	double 	pos_y;
	double	mini_pos_x;
	double	mini_pos_y;
	int		color;
	double	fov;
	int		p_size; // ?
	int		dist_to_p; // ?
	double	angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	float	ray_dir_x0;
	float	ray_dir_x1;
	float	ray_dir_y0;
	float	ray_dir_y1;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		b_pix;
	int		l_len;
	int		endian;
	int		width;
	int		height;
	t_player *player;
}	t_img;

typedef struct s_map
{
	int			length_max;
	int			nb_lines;
	int			unit_h_mini;
	int			unit_v_mini;
	int			unit_v;
	int			unit_h;
	char 		**parse_file;
	char		**map_tab;
	int			map_x; // pas utilse
	int			map_y; // pas utilise
	int			map_s; // pas utilise
	int			color;
	t_img		floor;
	t_img		ceiling;
	t_img		*wall_no;
	t_img		*wall_so;
	t_img		*wall_ea;
	t_img		*wall_we;
	int			rgb_floor;
	int			rgb_ceil;
	double		top_pix;
	double		bot_pix;
	double		height;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	t_player	*player;
	t_params	*par;
}	t_map;

typedef struct s_ray
{
	double	ray_angle;
	double	distance;
	int		flag;
}	t_ray;

typedef struct s_params
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_img		*mini_map;
	t_player	*player;
	t_map		*map;
	t_ray		*ray;
}	t_params;



/* Parsing */
int		check_av(t_map *map, char **str, int count);
int		check_map(char **str, t_map *map, int i);
int		check_color_params(char *str, int *rgb);
int		rgb_to_int(int r, int g, int b);
void	replace_spaces(char **str, t_map *map);
void	print_map(char **str);
void	print_tab(char **str, t_map *map);


/* Init */
void	count_alloc(t_map *map, char *file);
void	init_player_angle(t_player *player, char c, int i, int j);
void    init_structs(t_params *par);
void	init_t_map(t_params *par);
void	destroy(t_params *par);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_vertical_grid(t_img *img, t_map *map);
void	draw_horizontal_grid(t_img *img, t_map *map);
void    build_mini_map(t_img *img, t_map *map, t_params *par);

/* Draw */
void	clear_image(t_params *par);
void	draw_player(t_img *img, double x, double y, int color);
void	draw_walls(t_img *img, t_map *map, double *x, double *y, double saved_x, double saved_y);
void    floor_casting(t_params *par, t_player *player, t_map *map);

/* Events */
int		key_event(int keycode, t_params *par);
char	is_wall(t_map *map, double new_x, double new_y);

/* Raycast */
void	draw_fov(t_params *par, t_img *img, t_map *map, t_player *player, int color);
void	draw_3d(t_params *par, t_img *img, t_map *map, t_player *player, int color);
void    wall_casting(t_params *par, t_player *player, t_map *map);

#endif