# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 17:19:04 by cbridget          #+#    #+#              #
#    Updated: 2022/11/17 23:31:01 by cbridget         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

HEAD = headers/minirt.h headers/get_next_line.h headers/structs.h headers/transform.h

SRC = main.c utilities/utilities.c utilities/hooks.c utilities/init.c raytracer/minirt.c \
raytracer/raytracer.c utilities/vectors.c raytracer/intersect_sphere.c \
raytracer/compute_lighting.c raytracer/intersect_plane.c raytracer/intersect_cylinder.c \
utilities/vectors_two.c utilities/utilities_two.c  raytracer/intersect_lid.c\
transform/transform.c transform/change_obj.c transform/ch_view.c transform/resize.c \

SRC_PARCER = parcer/check_args.c parcer/check_params.c parcer/fill_info_1.c parcer/fill_info_2.c \
parcer/fill_info_3.c parcer/fill_valid.c parcer/init_info.c parcer/free.c parcer/parcer_basic_ft.c \
parcer/split.c parcer/get_next_line.c parcer/get_next_line_utils.c

SRC_PARCER_BONUS = parcer_bonus/check_args_bonus.c parcer_bonus/check_params_bonus.c parcer_bonus/fill_info_1_bonus.c parcer_bonus/fill_info_2_bonus.c \
parcer_bonus/fill_info_3_bonus.c parcer_bonus/fill_valid_bonus.c parcer_bonus/init_info_bonus.c parcer_bonus/free_bonus.c parcer_bonus/parcer_basic_ft_bonus.c \
parcer_bonus/split_bonus.c parcer_bonus/get_next_line_bonus.c parcer_bonus/get_next_line_utils_bonus.c

OBJ = $(addprefix objects/,$(SRC:.c=.o))

OBJ_PARCER = $(addprefix objects/,$(SRC_PARCER:.c=.o))

OBJ_PARCER_BONUS = $(addprefix objects/,$(SRC_PARCER_BONUS:.c=.o))

BUILD_FOLDERS := $(shell mkdir -p objects; mkdir -p objects/raytracer; mkdir -p objects/utilities; mkdir -p objects/transform; mkdir -p objects/parcer; mkdir -p objects/parcer_bonus)

FLAGS = -Wall -Wextra -Werror -O3

CC = cc

.PHONY : all clean fclean bonus re LIB MINILIBX

all : LIB MINILIBX $(NAME)

bonus : 
	make OBJ_PARCER="$(OBJ_PARCER_BONUS)" all

MINILIBX :
	$(MAKE) -C mlx_linux

LIB :
	$(MAKE) bonus -C libft

$(NAME) : $(OBJ) $(OBJ_PARCER)
	$(CC) $(FLAGS) $(OBJ) $(OBJ_PARCER) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lz -lm -Llibft -lft -o $(NAME)

objects/%.o : sources/%.c $(HEAD) Makefile libft/libft.a mlx_linux/libmlx.a
	$(CC) $(FLAGS) -iquote headers -iquote libft -I/usr/include -Imlx_linux -c $< -o $@

clean :
	rm -rf objects
	$(MAKE) clean -C libft
	$(MAKE) clean -C mlx_linux

fclean :
	rm -rf objects
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) clean -C mlx_linux

re :
	rm -rf objects/parcer/*.o
	rm -rf objects/parcer_bonus/*.o
	rm -rf objects/transform/*.o
	rm -rf objects/raytracer/*.o
	rm -rf objects/utilities/*.o
	rm -f $(NAME)
	$(MAKE) fclean -C libft
	$(MAKE) clean -C mlx_linux
	$(MAKE)
