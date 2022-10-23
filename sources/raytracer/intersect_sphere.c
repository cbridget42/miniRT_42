/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:23 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 17:51:27 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_sphere(t_ray *ray, t_sphere *sphere, t_answer *asw)
{
	t_coords	x;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	x = vector_subtraction(&ray->orig, &sphere->center);
	a = dot_vectors(&ray->dir, &ray->dir);
	b = 2.0f * dot_vectors(&x, &ray->dir);
	c = dot_vectors(&x, &x) - (sphere->radius * sphere->radius);
	discriminant = (b * b) - (4 * a * c);
	if (discriminant < EPS)
	{
		asw->t1 = __FLT_MAX__;
		asw->t2 = __FLT_MAX__;
		return ;
	}
	asw->t1 = (-b + sqrt(discriminant)) / (2 * a);
	asw->t2 = (-b - sqrt(discriminant)) / (2 * a);
}

void	closest_sphere(t_minirt *data, t_ray *ray, float t_min)
{
	t_list	*sphere_list;

	sphere_list = data->scene.spheres;
	while (sphere_list)
	{
		intersect_sphere(ray, sphere_list->content, &data->asw);
		if (data->asw.t1 >= t_min && data->asw.t1 < data->asw.closest_t \
			&& data->asw.t1 > EPS)
		{
			data->asw.closest_t = data->asw.t1;
			data->asw.closest_shape = sphere_list;
			data->asw.flag = SPHERE;
		}
		if (data->asw.t2 >= t_min && data->asw.t2 < data->asw.closest_t \
			&& data->asw.t1 > EPS)
		{
			data->asw.closest_t = data->asw.t2;
			data->asw.closest_shape = sphere_list;
			data->asw.flag = SPHERE;
		}
		sphere_list = sphere_list->next;
	}
}
