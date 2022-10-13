/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:27:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/13 19:36:37 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HIGHT 500
# define WIDTH 700
# define ESC 65307

# define SPHERE 101
# define PLANE 102
# define CYLINDER 103

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
	t_coordinates	center;
	float			radius;
	unsigned int	color;
}				t_sphere;

typedef struct	s_plane
{
	t_coordinates	center;
	t_coordinates	normal;
	unsigned int	color;
}				t_plane;


typedef struct	s_scene
{
	float		viewport_hight;
	float		viewport_width;
	t_list		*spheres;
	t_list		*planes;
}				t_scene;

typedef struct	s_camera
{
	t_coordinates	orig;
	t_coordinates	normal;
	float			fov;
	t_coordinates	x;
	t_coordinates	y;
	t_coordinates	z;
}				t_camera;

typedef struct	s_light_point
{
	t_coordinates	crdn;
	float			intensity;
	unsigned int	color;
}				t_light_point;

typedef struct	s_light_ambient
{
	float			intensity;
	unsigned int	color;
}				t_light_ambient;

typedef struct	s_answer
{
	float		t1;
	float		t2;
	float		closest_t;
	t_list		*closest_shape;
	char		flag;
}				t_answer;

typedef struct	s_minirt
{
	t_mlx			mlx;
	t_scene			scene;
	t_camera		camera;
	t_list			*light_p;
	t_light_ambient	light_a;
	t_answer		asw;//it contains the return value from the intersection functions.
}				t_minirt;

void			init_rt(t_minirt *data);

t_coordinates	vectorSubtraction(t_coordinates *a, t_coordinates *b);
t_coordinates	vectorAddition(t_coordinates *a, t_coordinates *b);
t_coordinates	multiplicationScalar(t_coordinates *x, float s);
float			dotVectors(t_coordinates *a, t_coordinates *b);
float			vectorLength(t_coordinates *x);
t_coordinates	vectorNarmolization(t_coordinates *x);
t_coordinates	cross_vectors(t_coordinates *a, t_coordinates *b);


void			config_cam(t_minirt	*data);
unsigned int	traceRay(t_minirt *data, t_coordinates *ray);
void			closestIntersection(t_minirt *data, t_coordinates *orig, t_coordinates *ray, float t_min);
void			rayTracing(t_minirt *data);
unsigned int	computeLighting(t_minirt *data, t_coordinates *pl, t_coordinates *norm, unsigned int color);
void			make_ray(t_minirt *data, t_coordinates *ray, float x, float y);
void			intersectRaySphere(t_coordinates *c, t_coordinates *ray, t_sphere *sphere, t_answer *asw);
void			closest_sphere(t_minirt *data, t_coordinates *v1, t_coordinates *v2, float t_min);
void			intersect_ray_plane(t_coordinates *orig, t_coordinates *ray, t_plane *plane, t_answer *asw);
void			closest_plane(t_minirt *data, t_coordinates *orig, t_coordinates *ray, float t_min);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
unsigned int	create_trgb(unsigned char r, unsigned char g, unsigned char b);
unsigned int	multiplicationColorByConstant(unsigned int color, float c);
unsigned int	multiply_light_channels(unsigned int c1, unsigned int c2, float c);
unsigned int	add_colors(unsigned int c1, unsigned int c2);
float			checkChannel(float canal);
int				select_keycode(int keycode, t_minirt *data);
int				ft_close(t_minirt *data);
void			del(void *d);

# endif
