/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computeLighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:56:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/05 19:21:28 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	computeLighting(t_minirt *data, t_coordinates *pl, t_coordinates *norm)
{
	t_answer		aws_shadow;
	t_coordinates	l_position;
	t_list			*light_list;
	float			i;
	float			n_dot_l;

	light_list = data->light_p;
	i = data->light_a.intensity;
	while (light_list)
	{
		l_position = vectorSubtraction(&((t_light_point *)light_list->content)->crdn, pl);
		aws_shadow = closestIntersection(data, pl, &l_position, 0.01f);
		if (aws_shadow.closest_sphere)
		{
			light_list = light_list->next;
			continue;
		}
		n_dot_l = dotVectors(norm, &l_position);
		if (n_dot_l > 0)
			i += ((t_light_point *)light_list->content)->intensity * n_dot_l / \
			(vectorLength(norm) * vectorLength(&l_position));
		light_list = light_list->next;
	}
	return (i);
}
