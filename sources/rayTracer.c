/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayTracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:39:21 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/04 15:40:02 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	traceRay(t_minirt *data, t_coordinates *viewport, float t_min, float t_max)
{
	float			closest_t;
	t_sphere		*closest_sphere;
	t_list			*sphere_list;
	t_answer		asw;
	t_coordinates	pl;
	t_coordinates	norm;

	closest_t = __FLT_MAX__;
	closest_sphere = NULL;
	sphere_list = data->scene.spheres;
	while (sphere_list)
	{
		intersectRaySphere(data, viewport, sphere_list->content, &asw);
		if ((asw.t1 >= t_min && asw.t1 <= t_max) && asw.t1 < closest_t)
		{
			closest_t = asw.t1;
			closest_sphere = sphere_list->content;
		}
		if ((asw.t2 >= t_min && asw.t2 <= t_max) && asw.t2 < closest_t)
		{
			closest_t = asw.t2;
			closest_sphere = sphere_list->content;
		}
		sphere_list = sphere_list->next;
	}
	if (closest_sphere == NULL)
		return (create_trgb(0, 0, 0));
	pl = multiplicationScalar(viewport, closest_t);
	pl = vectorAddition(&data->camera.crdn, &pl);
	norm = vectorSubtraction(&pl, &closest_sphere->center);
	norm = vectorNarmolization(&norm);
	return (multiplicationColorByConstant(closest_sphere->color, computeLighting(data, &pl, &norm)));
}
