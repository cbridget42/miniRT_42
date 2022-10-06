/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:39:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/06 19:37:58 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	traceRay(t_minirt *data, t_coordinates *ray)
{
	t_coordinates	pl;
	t_coordinates	norm;
	unsigned int	color;

	closestIntersection(data, &data->camera.crdn, ray, 1.0f);
	if (data->asw.closest_shape == NULL)
		return (create_trgb(0, 0, 0));
//	pl = multiplicationScalar(ray, data->asw.closest_t);
//	pl = vectorAddition(&data->camera.crdn, &pl);
	if (data->asw.flag == SPHERE)
	{
		pl = multiplicationScalar(ray, data->asw.closest_t);
		pl = vectorAddition(&data->camera.crdn, &pl);
		norm = vectorSubtraction(&pl, &((t_sphere *)(data->asw.closest_shape->content))->center);
		norm = vectorNarmolization(&norm);
		color = ((t_sphere *)(data->asw.closest_shape->content))->color;
	}
	else if (data->asw.flag == PLANE)
	{
//		return ((t_plane *)(data->asw.closest_shape->content))->color;
		pl = multiplicationScalar(ray, data->asw.closest_t);
		norm = ((t_plane *)(data->asw.closest_shape->content))->normal;
		color = ((t_plane *)(data->asw.closest_shape->content))->color;
	}
	return (multiplicationColorByConstant(color, computeLighting(data, &pl, &norm)));
}

void	closestIntersection(t_minirt *data, t_coordinates *v1, t_coordinates *v2, float t_min)
{
	data->asw.flag = 0;
	data->asw.closest_t = __FLT_MAX__;
	data->asw.closest_shape = NULL;
	closest_sphere(data, v1, v2, t_min);
	closest_plane(data, v1, v2, t_min);
}
