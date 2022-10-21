/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:39:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/21 18:26:28 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	trace_ray(t_minirt *data, t_ray *ray, float t_min, int depth)
{
	t_coords		norm;
	unsigned int	color;
	unsigned int	reflect_color;
	float			r;
	t_ray			r_ray;

	closest_intersection(data, ray, t_min);
	if (data->asw.closest_shape == NULL)
		return (create_trgb(0, 0, 0));
	r_ray.orig = multiplication_scalar(&ray->dir, data->asw.closest_t);
	r_ray.orig = vector_addition(&ray->orig, &r_ray.orig);
	r_ray.dir = multiplication_scalar(&ray->dir, -1.0f);
	norm = get_surface_normal(data, ray, &r_ray.orig);
	set_options(data, &r, &color);
	color = compute_lighting(data, &r_ray, &norm, color);
	if (!depth || r <= 0)
		return (color);
	r_ray.dir = reflect_ray(&norm, &r_ray.dir);
	reflect_color = trace_ray(data, &r_ray, 0.001f, depth - 1);
	return (add_colors(multiplication_color_constant(color, 1 - r), \
		multiplication_color_constant(reflect_color, r)));
}

void	closest_intersection(t_minirt *data, t_ray *ray, float t_min)
{
	data->asw.flag = 0;
	data->asw.closest_t = __FLT_MAX__;
	data->asw.closest_shape = NULL;
	closest_sphere(data, ray, t_min);
	closest_plane(data, ray, t_min);
	closest_cylinder(data, ray, t_min);
}

t_coords	get_surface_normal(t_minirt *data, t_ray *ray, t_coords *inter_p)
{
	t_coords	norm;

	if (data->asw.flag == SPHERE)
	{
		norm = vector_subtraction(inter_p, \
			&((t_sphere *)(data->asw.closest_shape->content))->center);
		norm = vector_narmolization(&norm);
	}
	else if (data->asw.flag == PLANE)
	{
		norm = ((t_plane *)(data->asw.closest_shape->content))->normal;
		if (dot_vectors(&ray->dir, &norm) > EPS)
			norm = multiplication_scalar(&norm, -1);
	}
	else
		norm = get_cylinder_norm(data, ray, inter_p);
	return (norm);
}

void	set_options(t_minirt *data, float *r, unsigned int *color)
{
	if (data->asw.flag == SPHERE)
	{
		*color = ((t_sphere *)(data->asw.closest_shape->content))->color;
		*r = ((t_sphere *)(data->asw.closest_shape->content))->reflect;
	}
	else if (data->asw.flag == PLANE)
	{
		*color = ((t_plane *)(data->asw.closest_shape->content))->color;
		*r = ((t_plane *)(data->asw.closest_shape->content))->reflect;
	}
	else
	{
		*color = ((t_cylinder *)data->asw.closest_shape->content)->color;
		*r = ((t_cylinder *)data->asw.closest_shape->content)->reflect;
	}
}
