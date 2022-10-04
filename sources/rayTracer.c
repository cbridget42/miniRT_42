/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:39:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/04 18:22:47 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	traceRay(t_minirt *data, t_coordinates *viewport, float t_min, float t_max)
{
	t_answer		asw;
	t_coordinates	pl;
	t_coordinates	norm;

	asw = closestIntersection(data, &data->camera.crdn, viewport, t_min, t_max);
	if (asw.closest_sphere == NULL)
		return (create_trgb(0, 0, 0));
	pl = multiplicationScalar(viewport, asw.closest_t);
	pl = vectorAddition(&data->camera.crdn, &pl);
	norm = vectorSubtraction(&pl, &asw.closest_sphere->center);
	norm = vectorNarmolization(&norm);
	return (multiplicationColorByConstant(asw.closest_sphere->color, computeLighting(data, &pl, &norm)));
}

t_answer	closestIntersection(t_minirt *data, t_coordinates *v1, t_coordinates *v2, float t_min, float t_max)
{
	t_list			*sphere_list;
	t_answer		asw;

	asw.closest_t = __FLT_MAX__;
	asw.closest_sphere = NULL;
	sphere_list = data->scene.spheres;
	while (sphere_list)
	{
		intersectRaySphere(v1, v2, sphere_list->content, &asw);
		if ((asw.t1 >= t_min && asw.t1 <= t_max) && asw.t1 < asw.closest_t)
		{
			asw.closest_t = asw.t1;
			asw.closest_sphere = sphere_list->content;
		}
		if ((asw.t2 >= t_min && asw.t2 <= t_max) && asw.t2 < asw.closest_t)
		{
			asw.closest_t = asw.t2;
			asw.closest_sphere = sphere_list->content;
		}
		sphere_list = sphere_list->next;
	}
	return (asw);
}
