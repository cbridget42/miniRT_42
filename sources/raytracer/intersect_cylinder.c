/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:16:19 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/26 16:10:24 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, t_answer *asw)
{
	t_coords	x;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	cylinder->normal = vector_narmolization(&cylinder->normal);
	x = vector_subtraction(&ray->orig, &cylinder->center);
	a = dot_vectors(&ray->dir, &ray->dir) - \
			(dot_vectors(&ray->dir, &cylinder->normal) \
			* dot_vectors(&ray->dir, &cylinder->normal));
	b = 2.0f * (dot_vectors(&x, &ray->dir) - (dot_vectors(&ray->dir, \
		&cylinder->normal) * dot_vectors(&x, &cylinder->normal)));
	c = dot_vectors(&x, &x) - (dot_vectors(&x, &cylinder->normal) * \
	dot_vectors(&x, &cylinder->normal)) - (cylinder->radius * cylinder->radius);
	discriminant = (b * b) - (4 * a * c);
	asw->t1 = (-b + sqrt(discriminant)) / (2 * a);
	if (discriminant < EPS || asw->t1 < EPS)
	{
		asw->t1 = __FLT_MAX__;
		asw->t2 = __FLT_MAX__;
		return ;
	}
	asw->t2 = (-b - sqrt(discriminant)) / (2 * a);
	intersect_cylinder_two(&x, ray, cylinder, asw);
}

void	intersect_cylinder_two(t_coords *x, t_ray *ray, \
					t_cylinder *cylinder, t_answer *asw)
{
	float		k1;
	float		k2;

	k1 = dot_vectors(&ray->dir, &cylinder->normal) \
			* asw->t2 + dot_vectors(x, &cylinder->normal);
	k2 = dot_vectors(&ray->dir, &cylinder->normal) \
			* asw->t1 + dot_vectors(x, &cylinder->normal);
	if (k1 > EPS && k1 <= cylinder->height)
		asw->t1 = asw->t2;
	else if (k2 > EPS && k2 <= cylinder->height)
		;
	else
		asw->t1 = __FLT_MAX__;
}

void	closest_cylinder(t_minirt *data, t_ray *ray, float t_min)
{
	t_list			*cylinder_list;

	cylinder_list = data->scene.cylinders;
	while (cylinder_list)
	{
		intersect_cylinder(ray, cylinder_list->content, &data->asw);
		if (data->asw.t1 >= t_min && data->asw.t1 < data->asw.closest_t \
			&& data->asw.t1 > EPS)
		{
			data->asw.closest_t = data->asw.t1;
			data->asw.closest_shape = cylinder_list;
			data->asw.flag = CYLINDER;
		}
		if (intersect_lid(ray, cylinder_list->content, &data->asw, t_min))
			data->asw.closest_shape = cylinder_list;
		cylinder_list = cylinder_list->next;
	}
}

t_coords	get_cylinder_norm(t_minirt *data, t_ray *ray, t_coords *inter_p)
{
	t_cylinder	cy_tmp;
	t_coords	a;
	t_coords	b;
	t_coords	res;
	float		m;

	cy_tmp = *((t_cylinder *)data->asw.closest_shape->content);
	a = multiplication_scalar(&cy_tmp.normal, data->asw.closest_t);
	b = vector_subtraction(&ray->orig, &cy_tmp.center);
	m = dot_vectors(&ray->dir, &a) + dot_vectors(&b, &cy_tmp.normal);
	a = vector_subtraction(inter_p, &cy_tmp.center);
	b = multiplication_scalar(&cy_tmp.normal, m);
	res = vector_subtraction(&a, &b);
	return (vector_narmolization(&res));
}
