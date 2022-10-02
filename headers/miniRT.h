/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:27:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/02 14:53:36 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HIGHT 700
# define WIDTH 700
# define ESC 65307

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct	s_coordinates
{
	float	x;
	float	y;
	float	z;
}				t_coordinates;


typedef struct	s_sphere
{
	t_coordinates		center;
	float				radius;
	unsigned int		color;
}				t_sphere;

typedef struct	s_scene
{
	int			viewport_size;
	int			projection_plane_d;
	t_list		*spheres;
}				t_scene;

typedef struct	s_camera
{
	t_coordinates	crdn;
}				t_camera;

typedef struct	s_minirt
{
	t_mlx		mlx;
	t_scene		scene;
	t_camera	camera;
}				t_minirt;

void	init_rt(t_minirt *data);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
int		select_keycode(int keycode, t_minirt *data);
int		ft_close(t_minirt *data);

# endif
