# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaubert <cmaubert@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 11:47:39 by cmaubert          #+#    #+#              #
#    Updated: 2025/02/25 12:12:36 by cmaubert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
FLAGS   = -Wall -Wextra -Werror -g -I$(HEADER) -I$(MLX) -I$(LIBFT)

NAME = cub3D
NAME_B = cub3D_bonus

LIBFT   = libft
OBJ_PATH  = objects
HEADER = includes
SRC_PATH  = sources
MLX      = mlx

SOURCES = main.c \
			color.c \
			draw.c \
			events.c \
			init.c \
			init_img.c \
			init_player.c \
			parse.c \
			parse_utils.c \
			parse_textures.c \
			raycast_3D.c \
			rotate.c \
			alloc.c \
			free.c \
			move.c 

SOURCES_B = main_bonus.c \
			mini_map_bonus.c \
			init_bonus.c \
			init_img_bonus.c \
			events_bonus.c \
			color.c \
			draw.c \
			init_player.c \
			parse.c \
			parse_utils.c \
			parse_textures.c \
			raycast_3D.c \
			rotate.c \
			alloc.c \
			free.c \
			move.c 

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
SRCS_B = $(addprefix $(SRC_PATH)/,$(SOURCES_B))
objects = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))
objects_bonus = $(addprefix $(OBJ_PATH)/,$(SOURCES_B:.c=.o))

all: lib tmp $(NAME)

lib:
	make -C $(LIBFT)
	make -C $(MLX)

$(NAME): $(objects)
	$(CC) $(FLAGS) -o $@ $^ -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm

$(NAME_B): $(objects_bonus)
	$(CC) $(FLAGS) -o $@ $^ -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm

tmp:
	mkdir -p objects

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/cub3d.h
	$(CC) $(FLAGS) -c -o $@ $<

bonus: lib tmp $(NAME_B) 

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_PATH)

fclean:
	rm -rf $(OBJ_PATH)
	rm -f $(NAME)
	rm -f $(NAME_B)
	make fclean -C $(LIBFT)

re: fclean
	$(MAKE) all

.PHONY: all, lib, tmp, re, fclean, clean