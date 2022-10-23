/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:10:03 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 19:43:12 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_radius(t_minirt *data, char sign)
{
	if (data->transform_flag == SPHERE && sign == '+')
		((t_sphere *)data->transform_obj)->radius += 0.5;
	if (data->transform_flag == SPHERE && sign == '-')
	{
		if (((t_sphere *)data->transform_obj)->radius - 0.5 < 0)
			((t_sphere *)data->transform_obj)->radius = 0;
		else
			((t_sphere *)data->transform_obj)->radius -= 0.5;
	}
	if (data->transform_flag == CYLINDER && sign == '+')
		((t_cylinder *)data->transform_obj)->radius += 0.5;
	if (data->transform_flag == CYLINDER && sign == '-')
	{
		if (((t_cylinder *)data->transform_obj)->radius - 0.5 < 0)
			((t_cylinder *)data->transform_obj)->radius = 0;
		else
			((t_cylinder *)data->transform_obj)->radius -= 0.5;
	}
	rerender(data, 0);
}

void	change_height(t_minirt *data, char sign)
{
	if (data->transform_flag == CYLINDER && sign == '+')
		((t_cylinder *)data->transform_obj)->height += 0.5;
	if (data->transform_flag == CYLINDER && sign == '-')
	{
		if (((t_cylinder *)data->transform_obj)->height - 0.5 < 0)
			((t_cylinder *)data->transform_obj)->height = 0;
		else
			((t_cylinder *)data->transform_obj)->height -= 0.5;
	}
	rerender(data, 0);
}
