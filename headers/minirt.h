/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:27:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 13:45:46 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define HIGHT 800
# define WIDTH 1300
# define ESC 65307
# define A 97
# define D 100
# define S 115
# define W 119
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define Q 113
# define E 101

# define SPECULAR 200
# define DEPTH 5

# define EPS 0.000001

# define SPHERE 106
# define PLANE 102
# define CYLINDER 103
# define CAM 104
# define LIGHT 105

//# define X 1001
//# define Y 1002
//# define Z 1003

# include "structs.h"
# include "transform.h"
# include <mlx.h>
# include <stdio.h>
# include <math.h>

void			init_rt(t_minirt *data);

t_coords		vector_subtraction(t_coords *a, t_coords *b);
t_coords		vector_addition(t_coords *a, t_coords *b);
t_coords		multiplication_scalar(t_coords *x, float s);
float			dot_vectors(t_coords *a, t_coords *b);
float			vector_length(t_coords *x);
t_coords		vector_narmolization(t_coords *x);
t_coords		cross_vectors(t_coords *a, t_coords *b);
t_coords		reflect_ray(t_coords *norm, t_coords *ray);
void			set_options(t_minirt *data, float *r, unsigned int *color);

void			config_cam(t_minirt	*data, int flag);
unsigned int	trace_ray(t_minirt *data, t_ray *ray, float t_min, int depth);
void			closest_intersection(t_minirt *data, t_ray *ray, float t_min);
t_coords		get_surface_normal(t_minirt *data, t_ray *ray, \
								t_coords *inter_p);
void			ray_tracing(t_minirt *data);
unsigned int	compute_lighting(t_minirt *data, t_ray *r_ray, \
								t_coords *norm, unsigned int color);
unsigned int	compute_intencity(t_list *light_list, t_coords *norm, \
								t_ray *r_ray, unsigned int color);
unsigned int	hi_norminette(t_list *light_list, unsigned int *color_p, \
								unsigned int color, int flag);
char			not_in_shadow(t_minirt *data, t_coords *inter_p, \
								t_coords *dir_light);
void			make_dir(t_minirt *data, t_coords *dir, float x, float y);
void			intersect_sphere(t_ray *ray, t_sphere *sphere, t_answer *asw);
void			closest_sphere(t_minirt *data, t_ray *ray, float t_min);
void			intersect_plane(t_ray *ray, t_plane *plane, t_answer *asw);
void			closest_plane(t_minirt *data, t_ray *ray, float t_min);
void			intersect_cylinder(t_ray *ray, t_cylinder *cylinder, \
								t_answer *asw);
void			intersect_cylinder_two(t_coords *x, t_ray *ray, \
								t_cylinder *cylinder, t_answer *asw);
void			closest_cylinder(t_minirt *data, t_ray *ray, float t_min);
t_coords		get_cylinder_norm(t_minirt *data, t_ray *ray, \
								t_coords *inter_p);
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
