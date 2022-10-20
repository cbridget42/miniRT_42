/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:56:51 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/20 19:23:37 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	compute_lighting(t_minirt *data, t_ray *r_ray, \
						t_coords *norm, unsigned int color)
{
	t_coords		dir_light;
	t_list			*light_list;
	unsigned int	color_p;

	color_p = 0;
	light_list = data->light_p;
	while (light_list)
	{
		dir_light = vector_subtraction(&((t_light_point *) \
						light_list->content)->coord, &r_ray->orig);
		if (not_in_shadow(data, &r_ray->orig, &dir_light))
			color_p = compute_intencity(light_list, norm, r_ray, color);
		else
			compute_intencity(light_list, norm, r_ray, 0xFFFFFFFF);
		light_list = light_list->next;
	}
	return (add_colors(multiply_light_channels(color, data->light_a.color, \
					data->light_a.intensity), color_p));
}

unsigned int	compute_intencity(t_list *light_list, t_coords *norm, \
							t_ray *r_ray, unsigned int color)
{
	t_coords			dr_light;
	float				n_dot_l;
	float				r_dot_v;
	static unsigned int	color_p;

	if (hi_norminette(light_list, &color_p, color, 0))
		return (0);
	dr_light = vector_subtraction(&((t_light_point *) \
						light_list->content)->coord, &r_ray->orig);
	dr_light = vector_narmolization(&dr_light);
	n_dot_l = dot_vectors(norm, &dr_light);
	if (n_dot_l > 0)
		color_p = add_colors(color_p, multiply_light_channels(color, \
		((t_light_point *)light_list->content)->color, \
		((t_light_point *)light_list->content)->intensity * n_dot_l));
	dr_light = reflect_ray(norm, &dr_light);
	r_dot_v = dot_vectors(&dr_light, &r_ray->dir);
	if (r_dot_v > 0)
		color_p = add_colors(color_p, multiply_light_channels(color, \
		((t_light_point *)light_list->content)->color, \
		((t_light_point *)light_list->content)->intensity * powf(r_dot_v / \
		(vector_length(&dr_light) * vector_length(&r_ray->dir)), SPECULAR)));
	return (hi_norminette(light_list, &color_p, color, 1));
}

unsigned int	hi_norminette(t_list *light_list, unsigned int *color_p, \
					unsigned int color, int flag)
{
	unsigned int	color_tmp;

	if (!light_list->next && (color == 0xFFFFFFFF || flag))
	{
		color_tmp = *color_p;
		*color_p = 0;
		if (flag)
			return (color_tmp);
		else
			return (42);
	}
	else if (color == 0xFFFFFFFF)
		return (42);
	else if (flag)
		return (*color_p);
	return (0);
}

unsigned int	multiply_light_channels(unsigned int c1, \
							unsigned int c2, float c)
{
	unsigned int	color;
	float			ch;

	color = 0;
	ch = (float)((c2 & 0x00FF0000) >> 16) / 255.0f;
	color |= (unsigned int)((float)((c1 & 0x00FF0000) >> 16) *ch) << 16;
	ch = (float)((c2 & 0x0000FF00) >> 8) / 255.0f;
	color |= (unsigned int)((float)((c1 & 0x0000FF00) >> 8) *ch) << 8;
	ch = (float)(c2 & 0x000000FF) / 255.0f;
	color |= (unsigned int)((float)(c1 & 0x000000FF) *ch);
	return (multiplication_color_constant(color, c));
}

char	not_in_shadow(t_minirt *data, t_coords *inter_p, t_coords *dir_light)
{
	t_coords	shadow;
	t_ray		r_light;

	r_light.orig = *inter_p;
	r_light.dir = *dir_light;
	closest_intersection(data, &r_light, 0.001f);
	shadow = multiplication_scalar(dir_light, data->asw.closest_t);
	shadow = vector_addition(inter_p, &shadow);
	shadow = vector_subtraction(&shadow, inter_p);
	if (data->asw.closest_t < __FLT_MAX__ && \
		(vector_length(dir_light) > vector_length(&shadow)))
		return (0);
	else
		return (1);
}
