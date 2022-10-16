/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:39:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/16 17:56:17 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	trace_ray(t_minirt *data, t_coords *ray)
{
	t_coords		inter_p;
	t_coords		norm;
	unsigned int	color;

	color = 0;
	closest_intersection(data, &data->camera.orig, ray, 1.0f);
	if (data->asw.closest_shape == NULL)
		return (create_trgb(0, 0, 0));
	inter_p = multiplication_scalar(ray, data->asw.closest_t);
	inter_p = vector_addition(&data->camera.orig, &inter_p);
	norm = get_surface_normal(data, &inter_p, ray);
	if (data->asw.flag == SPHERE)
		color = ((t_sphere *)(data->asw.closest_shape->content))->color;
	else if (data->asw.flag == PLANE)
		color = ((t_plane *)(data->asw.closest_shape->content))->color;
	else
		color = ((t_cylinder *)data->asw.closest_shape->content)->color;
	return (compute_lighting(data, &inter_p, &norm, color));
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
