/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:23 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/16 17:51:18 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_sphere(t_coords *orig, t_coords *ray, \
					t_sphere *sphere, t_answer *asw)
{
	t_coords	x;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	x = vector_subtraction(orig, &sphere->center);
	a = dot_vectors(ray, ray);
	b = 2.0f * dot_vectors(&x, ray);
	c = dot_vectors(&x, &x) - (sphere->radius * sphere->radius);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
	{
		asw->t1 = __FLT_MAX__;
		asw->t2 = __FLT_MAX__;
		return ;
	}
	asw->t1 = (-b + sqrt(discriminant)) / (2 * a);
	asw->t2 = (-b - sqrt(discriminant)) / (2 * a);
}

void	closest_sphere(t_minirt *data, t_coords *orig, \
						t_coords *ray, float t_min)
{
	t_list	*sphere_list;

	sphere_list = data->scene.spheres;
	while (sphere_list)
	{
		intersect_sphere(orig, ray, sphere_list->content, &data->asw);
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
