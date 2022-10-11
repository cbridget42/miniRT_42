/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computeLighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:56:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/11 14:15:46 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	computeLighting(t_minirt *data, t_coordinates *inter_p, t_coordinates *norm)
{
	t_coordinates	ray_light;
	t_coordinates	shadow;
	t_list			*light_list;
	float			i;
	float			n_dot_l;

	light_list = data->light_p;
	i = data->light_a.intensity;
	while (light_list)
	{
		ray_light = vectorSubtraction(&((t_light_point *)light_list->content)->crdn, inter_p);
		closestIntersection(data, inter_p, &ray_light, 0.001f);
		shadow = multiplicationScalar(&ray_light, data->asw.closest_t);
		shadow = vectorAddition(inter_p, &shadow);
		shadow = vectorSubtraction(&shadow, inter_p);
		if (data->asw.closest_t < __FLT_MAX__ && (vectorLength(&ray_light) > vectorLength(&shadow)))
		{
			light_list = light_list->next;
			continue;
		}
		ray_light = vectorNarmolization(&ray_light);
		n_dot_l = dotVectors(norm, &ray_light);
		if (n_dot_l > 0)
			i += ((t_light_point *)light_list->content)->intensity * n_dot_l;
		light_list = light_list->next;
	}
	return (i);
}
