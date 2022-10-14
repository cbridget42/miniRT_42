/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectRaySphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:23 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/13 23:22:13 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersectRaySphere(t_coordinates *orig, t_coordinates *ray, t_sphere *sphere, t_answer *asw)
{
	t_coordinates	x;
	float			k1;
	float			k2;
	float			k3;
	float			discriminant;

	x = vectorSubtraction(orig, &sphere->center);
	k1 = dotVectors(ray, ray);
	k2 = 2.0f * dotVectors(&x, ray);
	k3 = dotVectors(&x, &x) - (sphere->radius * sphere->radius);
	discriminant = (k2 * k2) - (4 * k1 * k3);
	if (discriminant < 0)
	{
		asw->t1 = __FLT_MAX__;
		asw->t2 = __FLT_MAX__;
		return;
	}
	asw->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	asw->t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
}

void	closest_sphere(t_minirt *data, t_coordinates *orig, t_coordinates *ray, float t_min)
{
	t_list			*sphere_list;

	sphere_list = data->scene.spheres;
	while (sphere_list)
	{
		intersectRaySphere(orig, ray, sphere_list->content, &data->asw);
		if (data->asw.t1 >= t_min && data->asw.t1 < data->asw.closest_t)
		{
			data->asw.closest_t = data->asw.t1;
			data->asw.closest_shape = sphere_list;
			data->asw.flag = SPHERE;
		}
		if (data->asw.t2 >= t_min && data->asw.t2 < data->asw.closest_t)
		{
			data->asw.closest_t = data->asw.t2;
			data->asw.closest_shape = sphere_list;
			data->asw.flag = SPHERE;
		}
		sphere_list = sphere_list->next;
	}
}
