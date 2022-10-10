/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:39:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/10 18:23:44 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	traceRay(t_minirt *data, t_coordinates *ray)
{
	t_coordinates	inter_p;
	t_coordinates	norm;
	unsigned int	color;

	closestIntersection(data, &data->camera.orig, ray, 1.0f);
	if (data->asw.closest_shape == NULL)
		return (create_trgb(0, 0, 0));
//	pl = multiplicationScalar(ray, data->asw.closest_t);
//	pl = vectorAddition(&data->camera.crdn, &pl);
	if (data->asw.flag == SPHERE)
	{
		inter_p = multiplicationScalar(ray, data->asw.closest_t);
		inter_p = vectorAddition(&data->camera.orig, &inter_p);
		norm = vectorSubtraction(&inter_p, &((t_sphere *)(data->asw.closest_shape->content))->center);
		norm = vectorNarmolization(&norm);
		color = ((t_sphere *)(data->asw.closest_shape->content))->color;
	}
	else if (data->asw.flag == PLANE)
	{
//		return ((t_plane *)(data->asw.closest_shape->content))->color;
		inter_p = multiplicationScalar(ray, data->asw.closest_t);
		inter_p = vectorAddition(&data->camera.orig, &inter_p);
		norm = ((t_plane *)(data->asw.closest_shape->content))->normal;
		if (dotVectors(ray, &norm) > __FLT_EPSILON__)
		{
			*ray = multiplicationScalar(ray, -1);
			norm = vectorNarmolization(ray);
		}
		color = ((t_plane *)(data->asw.closest_shape->content))->color;
	}
	return (multiplicationColorByConstant(color, computeLighting(data, &inter_p, &norm)));
}

void	closestIntersection(t_minirt *data, t_coordinates *orig, t_coordinates *ray, float t_min)
{
	data->asw.flag = 0;
	data->asw.closest_t = __FLT_MAX__;
	data->asw.closest_shape = NULL;
	closest_sphere(data, orig, ray, t_min);
	closest_plane(data, orig, ray, t_min);
}
