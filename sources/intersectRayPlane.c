/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectRayPlane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:40:58 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/11 14:34:05 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersect_ray_plane(t_coordinates *orig, t_coordinates *ray, t_plane *plane, t_answer *asw)
{
	t_coordinates	tmp_vec;
	float			a;
	float			b;

	plane->normal = vectorNarmolization(&plane->normal);
	b = dotVectors(ray, &plane->normal);
	if (!b)
	{
		asw->t1 = __FLT_MAX__;
		return;
	}
	tmp_vec = vectorSubtraction(orig, &plane->center);
	a = dotVectors(&tmp_vec, &plane->normal);
	asw->t1 = -a / b;
}

void	closest_plane(t_minirt *data, t_coordinates *orig, t_coordinates *ray, float t_min)
{
	t_list	*plane_list;

	plane_list = data->scene.planes;
	while (plane_list)
	{
		intersect_ray_plane(orig, ray, plane_list->content, &data->asw);
		if (data->asw.t1 >= t_min && data->asw.t1 < data->asw.closest_t)
		{
			data->asw.closest_t = data->asw.t1;
			data->asw.closest_shape = plane_list;
			data->asw.flag = PLANE;
		}
		plane_list = plane_list->next;
	}
}
