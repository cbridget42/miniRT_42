/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:16:19 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/16 13:57:33 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_cylinder(t_coords *orig, t_coords *ray, t_cylinder *cylinder, t_answer *asw)
{
	t_coords	x;
	float		k1;
	float		k2;
	float		k3;
	float		discriminant;
	float		a;
	float		b;

	cylinder->normal = vector_narmolization(&cylinder->normal);
	x = vector_subtraction(orig, &cylinder->center);
	k1 = dot_vectors(ray, ray) - (dot_vectors(ray, &cylinder->normal) * dot_vectors(ray, &cylinder->normal));
	k2 = 2.0f * (dot_vectors(&x, ray) - (dot_vectors(ray, &cylinder->normal) * dot_vectors(&x, &cylinder->normal)));
	k3 = dot_vectors(&x, &x) - (dot_vectors(&x, &cylinder->normal) * dot_vectors(&x, &cylinder->normal)) - (cylinder->radius * cylinder->radius);
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

	a = dot_vectors(ray, &cylinder->normal) * asw->t2 + dot_vectors(&x, &cylinder->normal);
	b = dot_vectors(ray, &cylinder->normal) * asw->t1 + dot_vectors(&x, &cylinder->normal);
	if (a > 0 && a <= cylinder->height)//???
		asw->t1 = asw->t2;
	else if (b > 0 && b <= cylinder->height)
		;
	else
		asw->t1 = __FLT_MAX__;
}

void	closest_cylinder(t_minirt *data, t_coords *orig, t_coords *ray, float t_min)
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
		cylinder_list = cylinder_list->next;
	}
}

t_coords	get_cylinder_norm(t_minirt *data, t_coords *orig, t_coords *ray, t_coords *inter_p)
{
	t_cylinder		cy_tmp;
	t_coords	a;
	t_coords	b;
	t_coords	res;
	float			m;

	cy_tmp = *((t_cylinder *)data->asw.closest_shape->content);
	a = multiplication_scalar(&cy_tmp.normal, data->asw.closest_t);
	b = vector_subtraction(orig, &cy_tmp.center);
	m = dot_vectors(ray, &a) + dot_vectors(&b, &cy_tmp.normal);
	a = vector_subtraction(inter_p, &cy_tmp.center);
	b = multiplication_scalar(&cy_tmp.normal, m);
	res = vector_subtraction(&a, &b);
	return (vector_narmolization(&res));
}
