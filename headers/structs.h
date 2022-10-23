/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:14:23 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 18:15:58 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libft.h"

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

typedef struct s_ray
{
	t_coords	orig;
	t_coords	dir;
}				t_ray;

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
	float			radius;
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
	t_answer		asw;
	int				transform_flag;
	int				norm_flag;
	void			*transform_obj;
}				t_minirt;

#endif
