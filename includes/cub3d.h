/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:55:04 by cmaubert          #+#    #+#             */
/*   Updated: 2025/02/25 11:24:47 by cmaubert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define TRUE 1
# define FALSE 0

# define HEIGHT_MINI 167 
# define WIDTH_MINI 256
# define HEIGHT 835
# define WIDTH 1280
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

typedef struct s_params	t_params;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	mini_x;
	double	mini_y;
	int		color;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move_left;
	int		move_rigth;
	int		move_up;
	int		move_down;
	int		left;
	int		rotate_rigth;
	int		mouse;
}	t_player;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			b_pix;
	int			l_len;
	int			endian;
	int			width;
	int			height;
	t_player	*player;
}	t_img;

typedef struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	dist_x;
	double	dist_y;
	double	delta_x;
	double	delta_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	tex_pos;
	double	step;
	int		color;
	t_img	*texture;
}	t_raycast;

typedef struct s_map
{
	int			length_max;
	int			nb_lines;
	double		h_mini;
	double		v_mini;
	char		**parse_file;
	char		**map_tab;
	t_img		floor;
	t_img		ceiling;
	t_img		*wall_no;
	t_img		*wall_so;
	t_img		*wall_ea;
	t_img		*wall_we;
	int			rgb_floor;
	int			rgb_ceil;
	double		height;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	t_player	*player;
	t_params	*par;
	int			flag;
	double		saved_x;
	double		saved_y;
}	t_map;

typedef struct s_params
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			fd;
	t_img		*img;
	t_img		*mini_map;
	t_player	*player;
	t_map		*map;
	t_raycast	*ray;
}	t_params;

/* Parsing */
int		check_map(char **str, t_map *map, int i);
int		check_color_params(char *str, int *rgb);
int		check_ext(char *map, char *ext);
int		rgb_to_int(int r, int g, int b);
void	replace_spaces(char **str, t_map *map);
int		final_all_path_filled(t_map *map);
int		temp_all_path_filled(t_map *map);
int		fill_color(char *str, t_map *map);
int		fill_texture_path(char *str, t_map *map);

/* Init images */
void	get_texture_address(t_map *map);
void	get_texture_path(t_map *map);
void	init_images(t_params *par, t_img *img);

/* Init */
void	init_structs(t_params *par);
void	init_t_map(t_params *par);
void	init_ray(t_raycast *ray, int x, t_player *player);

/* Init player */
void	init_player_angle(t_player *player, char c, int i, int j);

/* Draw */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	remove_fish_eye(t_raycast *ray);
void	draw_column_texture(int x, int *y, t_raycast *ray, t_params *par);
void	find_column_texture(t_raycast *ray, t_map *map, t_player *player);
void	draw_floor(t_params *par, t_map *map);

/* Mini_map */
void	draw_player(t_img *img, double x, double y, int color);
void	draw_walls(t_map *map, double *x, double *y);
void	build_mini_map(t_img *img, t_map *map, t_params *par);

/* Raycast */
void	wall_casting(t_params *par, t_player *player, t_map *map);

/* Events */
int		key_update(t_params *par);
int		key_press(int keycode, t_params *par);
int		key_release(int keycode, t_params *par);
int		mouse_event(int x, int y, t_params *par);
int		check_hit_and_update(t_map *map, double x, double y, t_player **player);

/* Rotate*/
void	left(t_player **p, double *o_dir_x, double *o_plane_x, double dist);
void	right(t_player **p, double *o_dir_x, double *o_plane_x, double dist);
void	rotate(t_player **player, double distance);
void	rotate_mouse(t_player **player, double dist, double delta_x);

/* Move */
void	move(t_map *map, t_player **player, double dist);

/* Free */
void	clean(t_params *par);
int		close_window(t_params *par);
void	free_tab(char **tab);

/* Alloc */
void	*clean_malloc(size_t size, t_params *par);
int		count_alloc(t_map *map, char *file);

/* Bonus */
void	init_images_b(t_params *par, t_img *img, t_img *mini_map);

#endif