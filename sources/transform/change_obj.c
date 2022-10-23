/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:27:12 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 18:14:11 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_obj(t_minirt *data)
{
	static int	i;
	static void	*obj_tmp;

	if (i == 0 || i == 1)
		change_sphere(data, &obj_tmp, &i);
	else if (i == 2 || i == 3)
		change_plane(data, &obj_tmp, &i);
	else if (i == 4 || i == 5)
		change_cylinder(data, &obj_tmp, &i);
	else if (i == 6 || i == 7)
		change_light(data, &obj_tmp, &i);
	else if (i == 8)
	{
		data->transform_obj = &data->camera;
		data->transform_flag = CAM;
		printf("Selected camera!\n");
		i = 0;
	}
}

void	change_light(t_minirt *data, void **obj_tmp, int *i)
{
	if (*i == 6)
	{
		if (data->light_p)
		{
			data->transform_obj = data->light_p->content;
			data->transform_flag = LIGHT;
			*obj_tmp = data->light_p;
			printf("Selected light!\n");
		}
		else
			*obj_tmp = NULL;
		*i += 1;
	}
	else if (*i == 7)
	{
		if (*obj_tmp && ((t_list *)*obj_tmp)->next)
		{
			*obj_tmp = ((t_list *)*obj_tmp)->next;
			data->transform_obj = ((t_list *)*obj_tmp)->content;
			data->transform_flag = LIGHT;
			printf("Selected light!\n");
		}
		else
			*i += 1;
	}
}

void	change_cylinder(t_minirt *data, void **obj_tmp, int *i)
{
	if (*i == 4)
	{
		if (data->scene.cylinders)
		{
			data->transform_obj = data->scene.cylinders->content;
			data->transform_flag = CYLINDER;
			*obj_tmp = data->scene.cylinders;
			printf("Selected cylinder!\n");
		}
		else
			*obj_tmp = NULL;
		*i += 1;
	}
	else if (*i == 5)
	{
		if (*obj_tmp && ((t_list *)*obj_tmp)->next)
		{
			*obj_tmp = ((t_list *)*obj_tmp)->next;
			data->transform_obj = ((t_list *)*obj_tmp)->content;
			data->transform_flag = CYLINDER;
			printf("Selected cylinder!\n");
		}
		else
			*i += 1;
	}
}

void	change_plane(t_minirt *data, void **obj_tmp, int *i)
{
	if (*i == 2)
	{
		if (data->scene.planes)
		{
			data->transform_obj = data->scene.planes->content;
			data->transform_flag = PLANE;
			*obj_tmp = data->scene.planes;
			printf("Selected plane!\n");
		}
		else
			*obj_tmp = NULL;
		*i += 1;
	}
	else if (*i == 3)
	{
		if (*obj_tmp && ((t_list *)*obj_tmp)->next)
		{
			*obj_tmp = ((t_list *)*obj_tmp)->next;
			data->transform_obj = ((t_list *)*obj_tmp)->content;
			data->transform_flag = PLANE;
			printf("Selected plane!\n");
		}
		else
			*i += 1;
	}
}

void	change_sphere(t_minirt *data, void **obj_tmp, int *i)
{
	if (*i == 0)
	{
		if (data->scene.spheres)
		{
			data->transform_obj = data->scene.spheres->content;
			data->transform_flag = SPHERE;
			*obj_tmp = data->scene.spheres;
			printf("Selected sphere!\n");
		}
		else
			*obj_tmp = NULL;
		*i += 1;
	}
	else if (*i == 1)
	{
		if (*obj_tmp && ((t_list *)*obj_tmp)->next)
		{
			*obj_tmp = ((t_list *)*obj_tmp)->next;
			data->transform_obj = ((t_list *)*obj_tmp)->content;
			data->transform_flag = SPHERE;
			printf("Selected sphere!\n");
		}
		else
			*i += 1;
	}
}
