/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:56:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/16 16:55:22 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	compute_lighting(t_minirt *data, t_coords *inter_p, \
						t_coords *norm, unsigned int color)
{
	t_coords		ray_light;
	t_list			*light_list;
	unsigned int	color_p;
	float			n_dot_l;

	color_p = 0;
	light_list = data->light_p;
	while (light_list)
	{
		ray_light = vector_subtraction(&((t_light_point *) \
						light_list->content)->coord, inter_p);
		if (not_in_shadow(data, inter_p, &ray_light))
		{
			ray_light = vector_narmolization(&ray_light);
			n_dot_l = dot_vectors(norm, &ray_light);
			if (n_dot_l > 0)
				color_p = add_colors(color_p, multiply_light_channels(color, \
				((t_light_point *)light_list->content)->color, \
				((t_light_point *)light_list->content)->intensity * n_dot_l));
		}
		light_list = light_list->next;
	}
	return (add_colors(multiply_light_channels(color, data->light_a.color, \
					data->light_a.intensity), color_p));
}

unsigned int	multiply_light_channels(unsigned int c1, \
							unsigned int c2, float c)
{
	unsigned int	color;
	float			ch;

	color = 0;
	ch = (float)((c2 & 0x00FF0000) >> 16) / 255.0f;
	if (ch < 0.0001f)
		ch = 0.3f;
	color |= (unsigned int)((float)((c1 & 0x00FF0000) >> 16) *ch) << 16;
	ch = (float)((c2 & 0x0000FF00) >> 8) / 255.0f;
	if (ch < 0.0001f)
		ch = 0.3f;
	color |= (unsigned int)((float)((c1 & 0x0000FF00) >> 8) *ch) << 8;
	ch = (float)(c2 & 0x000000FF) / 255.0f;
	if (ch < 0.0001f)
		ch = 0.3f;
	color |= (unsigned int)((float)(c1 & 0x000000FF) *ch);
	return (multiplication_color_constant(color, c));
}

char	not_in_shadow(t_minirt *data, t_coords *inter_p, t_coords *ray_light)
{
	t_coords	shadow;

	closest_intersection(data, inter_p, ray_light, 0.001f);
	shadow = multiplication_scalar(ray_light, data->asw.closest_t);
	shadow = vector_addition(inter_p, &shadow);
	shadow = vector_subtraction(&shadow, inter_p);
	if (data->asw.closest_t < __FLT_MAX__ && \
		(vector_length(ray_light) > vector_length(&shadow)))
		return (0);
	else
		return (1);
}
