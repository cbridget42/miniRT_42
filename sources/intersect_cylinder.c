/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:16:19 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/15 14:55:24 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersect_cylinder(t_coordinates *orig, t_coordinates *ray, t_cylinder *cylinder, t_answer *asw)
{
	t_coordinates	x;
	float			k1;
	float			k2;
	float			k3;
	float			discriminant;

	float			a;
	float			b;

	cylinder->normal = vectorNarmolization(&cylinder->normal);
	x = vectorSubtraction(orig, &cylinder->center);
	k1 = dotVectors(ray, ray) - (dotVectors(ray, &cylinder->normal) * dotVectors(ray, &cylinder->normal));
	k2 = 2.0f * (dotVectors(&x, ray) - (dotVectors(ray, &cylinder->normal) * dotVectors(&x, &cylinder->normal)));
	k3 = dotVectors(&x, &x) - (dotVectors(&x, &cylinder->normal) * dotVectors(&x, &cylinder->normal)) - (cylinder->radius * cylinder->radius);
	discriminant = (k2 * k2) - (4 * k1 * k3);
	asw->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);//???
	if (discriminant < 0 || asw->t1 < 0)
	{
		asw->t1 = __FLT_MAX__;
		asw->t2 = __FLT_MAX__;
		return;
	}
//	asw->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	asw->t2 = (-k2 - sqrt(discriminant)) / (2 * k1);

	a = dotVectors(ray, &cylinder->normal) * asw->t2 + dotVectors(&x, &cylinder->normal);
	b = dotVectors(ray, &cylinder->normal) * asw->t1 + dotVectors(&x, &cylinder->normal);
	if (a > 0 && a <= cylinder->height)//???
		asw->t1 = asw->t2;
	else if (b > 0 && b <= cylinder->height)
		;
	else
		asw->t1 = __FLT_MAX__;
}

void	closest_cylinder(t_minirt *data, t_coordinates *orig, t_coordinates *ray, float t_min)
{
	t_list			*cylinder_list;

	cylinder_list = data->scene.cylinders;
	while (cylinder_list)
	{
		intersect_cylinder(orig, ray, cylinder_list->content, &data->asw);
		if (data->asw.t1 >= t_min && data->asw.t1 < data->asw.closest_t)
		{
			data->asw.closest_t = data->asw.t1;
			data->asw.closest_shape = cylinder_list;
			data->asw.flag = CYLINDER;
		}
/*		if (data->asw.t2 >= t_min && data->asw.t2 < data->asw.closest_t)
		{
			data->asw.closest_t = data->asw.t2;
			data->asw.closest_shape = sphere_list;
			data->asw.flag = SPHERE;
		}*/
		cylinder_list = cylinder_list->next;
	}
}

t_coordinates	get_cylinder_norm(t_minirt *data, t_coordinates *orig, t_coordinates *ray, t_coordinates *inter_p)
{
	t_cylinder		cy_tmp;
	t_coordinates	a;
	t_coordinates	b;
	t_coordinates	res;
	float			m;

	cy_tmp = *((t_cylinder *)data->asw.closest_shape->content);
	a = multiplicationScalar(&cy_tmp.normal, data->asw.closest_t);
	b = vectorSubtraction(orig, &cy_tmp.center);
	m = dotVectors(ray, &a) + dotVectors(&b, &cy_tmp.normal);
	a = vectorSubtraction(inter_p, &cy_tmp.center);
	b = multiplicationScalar(&cy_tmp.normal, m);
	res = vectorSubtraction(&a, &b);
	return (vectorNarmolization(&res));
}
