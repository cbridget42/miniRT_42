/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computeLighting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:56:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/13 19:41:43 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned int	computeLighting(t_minirt *data, t_coordinates *inter_p, t_coordinates *norm, unsigned int color)
{
	t_coordinates	ray_light;
	t_coordinates	shadow;
	t_list			*light_list;
	unsigned int	color_a;
	unsigned int	color_p;
	unsigned int	color_tmp;
	float			n_dot_l;

	color_p = 0;
	light_list = data->light_p;
	color_a = multiply_light_channels(color, data->light_a.color, data->light_a.intensity);
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
		{
			color_tmp = multiply_light_channels(color, ((t_light_point *)light_list->content)->color, ((t_light_point *)light_list->content)->intensity * n_dot_l);
			color_p = add_colors(color_p, color_tmp);
		}
		light_list = light_list->next;
	}
	return (add_colors(color_a, color_p));
}

unsigned int	multiply_light_channels(unsigned int c1, unsigned int c2, float c)
{
	unsigned int	color;
	float			ch;

	color = 0;
	ch = (float)((c2 & 0x00FF0000) >> 16) / 255.0f;
	if (ch < 0.0001f)
		ch = 0.3f;
	color |= (unsigned int)((float)((c1 & 0x00FF0000) >> 16) * ch) << 16;
	ch = (float)((c2 & 0x0000FF00) >> 8) / 255.0f;
	if (ch < 0.0001f)
		ch = 0.3f;
	color |= (unsigned int)((float)((c1 & 0x0000FF00) >> 8) * ch) << 8;
	ch = (float)(c2 & 0x000000FF) / 255.0f;
	if (ch < 0.0001f)
		ch = 0.3f;
	color |= (unsigned int)((float)(c1 & 0x000000FF) * ch);

	return (multiplicationColorByConstant(color, c));
}
