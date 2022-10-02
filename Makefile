# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 17:19:04 by cbridget          #+#    #+#              #
#    Updated: 2022/10/02 14:54:20 by cbridget         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

HEAD = headers/miniRT.h

SRC = main.c utilities.c hooks.c init.c

OBJ = $(addprefix objects/,$(SRC:.c=.o))

BUILD_FOLDER := $(shell mkdir -p objects)

FLAGS = -Wall -Wextra #-Werror -O3

CC = cc

.PHONY : all clean fclean bonus re LIB MINILIBX

all : LIB MINILIBX $(NAME)

MINILIBX :
	$(MAKE) -C mlx_linux

LIB :
	$(MAKE) bonus -C libft

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -Llibft -o $(NAME)

objects/%.o : sources/%.c $(HEAD) Makefile libft/libft.a mlx_linux/libmlx.a
	$(CC) $(FLAGS) -iquote headers -iquote libft -I/usr/include -Imlx_linux -c $< -o $@

bonus : all

clean :
	rm -rf objects
	$(MAKE) clean -C libft

fclean :
	rm -rf objects
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re :
	rm -r objects/*.o
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE)
