/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computeLighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:56:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/10 19:25:19 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	computeLighting(t_minirt *data, t_coordinates *inter_p, t_coordinates *norm)
{
	t_coordinates	inter_light;
	t_list			*light_list;
	float			i;
	float			n_dot_l;

	t_coordinates	inter_shed;

	light_list = data->light_p;
	i = data->light_a.intensity;
	while (light_list)
	{
		inter_light = vectorSubtraction(&((t_light_point *)light_list->content)->crdn, inter_p);
		inter_light = vectorNarmolization(&inter_light);
		closestIntersection(data, inter_p, &inter_light, 0.1f);
		
		inter_light = vectorSubtraction(&((t_light_point *)light_list->content)->crdn, inter_p);
		inter_shed = multiplicationScalar(&inter_light, data->asw.closest_t);
		inter_shed = vectorAddition(inter_p, &inter_shed);
		if (/*data->asw.closest_shape && data->asw.flag != PLANE*/data->asw.closest_t < __FLT_MAX__ && (vectorLength(&inter_light) > vectorLength(&inter_shed)))
		{
			light_list = light_list->next;
			continue;
		}
		n_dot_l = dotVectors(norm, &inter_light);
		if (n_dot_l > 0)
//			i += ((t_light_point *)light_list->content)->intensity * n_dot_l /
//			(vectorLength(norm) * vectorLength(&l_position));
			i += ((t_light_point *)light_list->content)->intensity * n_dot_l;
		light_list = light_list->next;
	}
	return (i);
}
