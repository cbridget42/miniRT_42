/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:39:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/18 19:16:17 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	trace_ray(t_minirt *data, t_coords *orig, t_coords *ray, float t_min, int depth)
{
	t_coords		inter_p;
	t_coords		norm;
	unsigned int	color;

	unsigned int	local_color;
	unsigned int	reflect_color;

	color = 0;
	closest_intersection(data, orig, ray, t_min);
	if (data->asw.closest_shape == NULL)
		return (create_trgb(0, 0, 0));
	inter_p = multiplication_scalar(ray, data->asw.closest_t);
	inter_p = vector_addition(orig, &inter_p);
	norm = get_surface_normal(data, &inter_p, ray);
	float r;
	if (data->asw.flag == SPHERE)
	{
		color = ((t_sphere *)(data->asw.closest_shape->content))->color;
		r = ((t_sphere *)(data->asw.closest_shape->content))->reflect;
	}
	else if (data->asw.flag == PLANE)
	{
		color = ((t_plane *)(data->asw.closest_shape->content))->color;
		r = ((t_plane *)(data->asw.closest_shape->content))->reflect;
	}
	else
	{
		color = ((t_cylinder *)data->asw.closest_shape->content)->color;
		r = ((t_cylinder *)data->asw.closest_shape->content)->reflect;
	}

	t_coords r_ray = multiplication_scalar(ray, -1.0f);
	local_color = compute_lighting(data, &inter_p, &norm, &r_ray, color);

//	float r = ;//fix it
	t_coords reflect;
	if (depth <= 0 || r <= 0)
		return (local_color);
	reflect = reflect_ray(&norm, &r_ray);
	reflect_color = trace_ray(data, &inter_p, &reflect, 0.001f, depth - 1);
	return (add_colors(multiplication_color_constant(local_color, 1 - r), multiplication_color_constant(reflect_color, r)));
//	return local_color;

//	return (compute_lighting(data, &inter_p, &norm, multiplication_scalar(ray, -1), color));
}

void	closest_intersection(t_minirt *data, t_coords *orig, \
						t_coords *ray, float t_min)
{
	data->asw.flag = 0;
	data->asw.closest_t = __FLT_MAX__;
	data->asw.closest_shape = NULL;
	closest_sphere(data, orig, ray, t_min);
	closest_plane(data, orig, ray, t_min);
	closest_cylinder(data, orig, ray, t_min);
}

t_coords	get_surface_normal(t_minirt *data, t_coords *inter_p, t_coords *ray)
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
		if (dot_vectors(ray, &norm) > __FLT_EPSILON__)
		{
			*ray = multiplication_scalar(ray, -1);
			norm = vector_narmolization(ray);
		}
	}
	else
		norm = get_cylinder_norm(data, &data->camera.orig, ray, inter_p);
	return (norm);
}
