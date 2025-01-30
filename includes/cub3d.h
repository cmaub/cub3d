/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvander <anvander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:55:04 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/30 15:50:10 by anvander         ###   ########.fr       */
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

int	rgb_to_int(int r, int g, int b);
int	check_map(char **str, t_map *map, int i);


#endif