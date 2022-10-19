/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:40:58 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/19 13:59:15 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_plane(t_coords *orig, t_coords *ray, \
					t_plane *plane, t_answer *asw)
{
	t_coords	tmp_vec;
	float		a;
	float		b;

	plane->normal = vector_narmolization(&plane->normal);
	tmp_vec = vector_subtraction(orig, &plane->center);
	a = dot_vectors(&tmp_vec, &plane->normal);
	b = dot_vectors(ray, &plane->normal);
	if (!b || (a < 0 && b < 0) || (a > 0 && b > 0))
	{
		asw->t1 = __FLT_MAX__;
		return ;
	}
//	tmp_vec = vector_subtraction(orig, &plane->center);
//	a = dot_vectors(&tmp_vec, &plane->normal);
	asw->t1 = -a / b;
	if (asw->t1 < __FLT_EPSILON__)
	{
		asw->t1 = __FLT_MAX__;
		return ;
	}
}

void	closest_plane(t_minirt *data, t_coords *orig, \
					t_coords *ray, float t_min)
{
	t_list	*plane_list;

	plane_list = data->scene.planes;
	while (plane_list)
	{
		intersect_plane(orig, ray, plane_list->content, &data->asw);
		if (data->asw.t1 >= t_min && data->asw.t1 < data->asw.closest_t)
		{
			data->asw.closest_t = data->asw.t1;
			data->asw.closest_shape = plane_list;
			data->asw.flag = PLANE;
		}
		plane_list = plane_list->next;
	}
}
