/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:27:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/03 16:17:46 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HIGHT 500
# define WIDTH 500
# define ESC 65307

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>

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
	int			viewport_hight;
	int			viewport_width;
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

typedef struct	s_answer
{
	float	t1;
	float	t2;
}				t_answer;

void			init_rt(t_minirt *data);
t_coordinates	vectorSubtraction(t_coordinates *a, t_coordinates *b);
float			dotVectors(t_coordinates *a, t_coordinates *b);
unsigned int	traceRay(t_minirt *data, t_coordinates *viewport, float t_min, float t_max);
void			rayTracing(t_minirt *data);
void			canvasToViewport(t_minirt *data, t_coordinates *vp, float x, float y);
void			intersectRaySphere(t_minirt *data, t_coordinates *viewport, t_sphere *sphere, t_answer *asw);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
unsigned int	create_trgb(unsigned char r, unsigned char g, unsigned char b);
int				select_keycode(int keycode, t_minirt *data);
int				ft_close(t_minirt *data);
void			del(void *d);

# endif
