# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvander <anvander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 11:47:39 by cmaubert          #+#    #+#              #
#    Updated: 2025/02/04 16:30:44 by anvander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
FLAGS   = -Wall -Wextra -Werror -g -I$(HEADER) -I$(MLX) -I$(LIBFT)

NAME = cub3D

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
			parse.c \
			parse_utils.c 

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
objects = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

all: lib tmp $(NAME)

lib:
	make -C $(LIBFT)
	make -C $(MLX)

$(NAME): $(objects)
	$(CC) $(FLAGS) -o $@ $^ -L$(LIBFT) -lft -L$(MLX) -lmlx -lXext -lX11 -lm

tmp:
	mkdir -p objects

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/cub3d.h
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJ_PATH)

fclean:
	rm -rf $(OBJ_PATH)
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean
	$(MAKE) all

.PHONY: all, lib, tmp, re, fclean, clean