/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:27:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/18 19:12:42 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HIGHT 800
# define WIDTH 1300
# define ESC 65307

# define SPECULAR 200

# define SPHERE 101
# define PLANE 102
# define CYLINDER 103

# include "libft.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
}				t_coords;

typedef struct s_sphere
{
	t_coords		center;
	float			radius;
	unsigned int	color;
	float			reflect;
}				t_sphere;

typedef struct s_plane
{
	t_coords		center;
	t_coords		normal;
	unsigned int	color;
	float			reflect;
}				t_plane;

typedef struct t_cylinder
{
	t_coords		center;
	t_coords		normal;
	float			radius;//diameter should be divided by two
	float			height;
	unsigned int	color;
	float			reflect;
}				t_cylinder;

typedef struct s_scene
{
	float		viewport_hight;
	float		viewport_width;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}				t_scene;

typedef struct s_camera
{
	t_coords	orig;
	t_coords	normal;
	float		fov;
	t_coords	x;
	t_coords	y;
	t_coords	z;
}				t_camera;

typedef struct s_light_point
{
	t_coords		coord;
	float			intensity;
	unsigned int	color;
}				t_light_point;

typedef struct s_light_ambient
{
	float			intensity;
	unsigned int	color;
}				t_light_ambient;

typedef struct s_answer
{
	float		t1;
	float		t2;
	float		closest_t;
	t_list		*closest_shape;
	char		flag;
}				t_answer;

typedef struct s_minirt
{
	t_mlx			mlx;
	t_scene			scene;
	t_camera		camera;
	t_list			*light_p;
	t_light_ambient	light_a;
	t_answer		asw;//it contains the return value from the intersection functions.
}				t_minirt;

void			init_rt(t_minirt *data);

t_coords		vector_subtraction(t_coords *a, t_coords *b);
t_coords		vector_addition(t_coords *a, t_coords *b);
t_coords		multiplication_scalar(t_coords *x, float s);
float			dot_vectors(t_coords *a, t_coords *b);
float			vector_length(t_coords *x);
t_coords		vector_narmolization(t_coords *x);
t_coords		cross_vectors(t_coords *a, t_coords *b);
t_coords		reflect_ray(t_coords *norm, t_coords *ray);

void			config_cam(t_minirt	*data);
unsigned int	trace_ray(t_minirt *data, t_coords *orig, t_coords *ray, float t_min, int depth);
void			closest_intersection(t_minirt *data, t_coords *orig, \
								t_coords *ray, float t_min);
t_coords		get_surface_normal(t_minirt *data, \
								t_coords *inter_p, t_coords *ray);
void			ray_tracing(t_minirt *data);
unsigned int	compute_lighting(t_minirt *data, t_coords *pl, \
								t_coords *norm, t_coords *r_ray, unsigned int color);
char			not_in_shadow(t_minirt *data, t_coords *inter_p, \
								t_coords *ray_light);
void			make_ray(t_minirt *data, t_coords *ray, float x, float y);
void			intersect_sphere(t_coords *orig, t_coords *ray, \
								t_sphere *sphere, t_answer *asw);
void			closest_sphere(t_minirt *data, t_coords *orig, \
								t_coords *ray, float t_min);
void			intersect_plane(t_coords *orig, t_coords *ray, \
								t_plane *plane, t_answer *asw);
void			closest_plane(t_minirt *data, t_coords *orig, \
								t_coords *ray, float t_min);
void			intersect_cylinder(t_coords *orig, t_coords *ray, \
								t_cylinder *cylinder, t_answer *asw);
void			intersect_cylinder_two(t_coords *x, t_coords *ray, \
								t_cylinder *cylinder, t_answer *asw);
void			closest_cylinder(t_minirt *data, t_coords *orig, \
								t_coords *ray, float t_min);
t_coords		get_cylinder_norm(t_minirt *data, t_coords *orig, \
								t_coords *ray, t_coords *inter_p);
void			my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
unsigned int	create_trgb(unsigned char r, unsigned char g, unsigned char b);
unsigned int	multiplication_color_constant(unsigned int color, float c);
unsigned int	multiply_light_channels(unsigned int c1, \
								unsigned int c2, float c);
unsigned int	add_colors(unsigned int c1, unsigned int c2);
float			check_channel(float canal);
int				select_keycode(int keycode, t_minirt *data);
int				ft_close(t_minirt *data);
void			del(void *d);

#endif
