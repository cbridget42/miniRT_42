/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_lid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:08:32 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/26 16:11:46 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_lid(t_ray *ray, t_cylinder *cylinder, t_answer *asw, float t_min)
{
	t_plane		lid;
	int			res;

	res = 0;
	lid.center = cylinder->normal;
	lid.center = multiplication_scalar(&lid.center, cylinder->height);
	lid.center = vector_addition(&lid.center, &cylinder->center);
	lid.normal = cylinder->normal;
	asw->t_min = t_min;
	if (check_intr_lid(ray, cylinder, &lid, asw))
		res = 1;
	lid.center = cylinder->center;
	lid.normal = cylinder->normal;
	if (check_intr_lid(ray, cylinder, &lid, asw))
		res = 1;
	return (res);
}

int	check_intr_lid(t_ray *ray, t_cylinder *cylinder, \
				t_plane *lid, t_answer *asw)
{
	t_coords	p_tmp;

	intersect_plane(ray, lid, &asw->t1);
	if (asw->t1 < __FLT_MAX__)
	{
		p_tmp = multiplication_scalar(&ray->dir, asw->t1);
		p_tmp = vector_addition(&ray->orig, &p_tmp);
		if (powf(p_tmp.x - lid->center.x, 2) + \
		powf(p_tmp.y - lid->center.y, 2) + \
		powf(p_tmp.z - lid->center.z, 2) <= \
		powf(cylinder->radius, 2) && asw->t1 >= \
		asw->t_min && asw->t1 < asw->closest_t \
			&& asw->t1 > EPS)
		{
			asw->closest_t = asw->t1;
			asw->flag = LID;
			asw->norm_lid = lid->normal;
			return (1);
		}
	}
	return (0);
}
