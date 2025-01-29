/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:55:04 by cmaubert          #+#    #+#             */
/*   Updated: 2025/01/29 12:37:41 by cmaubert         ###   ########.fr       */
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

typedef struct s_player
{
	double pos_x;
	double pos_y;
	int	color;
}	t_player;

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

typedef struct s_params
{
	void		*mlx_ptr;
	void		*win_ptr;
	// t_map	*map;
	t_img		img;
	t_player	player;
}	t_params;

int	rgb_to_int(int r, int g, int b);

#endif