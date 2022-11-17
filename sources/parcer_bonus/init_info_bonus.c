/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 05:21:36 by ymirna            #+#    #+#             */
/*   Updated: 2022/10/24 05:02:55 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_point(t_minirt	*info, t_list	**list)
{
	t_light_point	*l_p;

	l_p = malloc(sizeof(t_light_point) * 1);
	if (!l_p)
	{
		info->info_error = 6;
		return (1);
	}
	if (!info->check.l_p)
		info->light_p = ft_lstnew(l_p);
	else
		ft_lstadd_back(&info->light_p, ft_lstnew(l_p));
	*list = info->light_p;
	while ((*list)->next != NULL)
		*list = (*list)->next;
	return (0);
}

int	init_sphere(t_minirt	*info, t_list	**list)
{
	t_light_point	*sph;

	sph = malloc(sizeof(t_sphere) * 1);
	if (!sph)
	{
		info->info_error = 6;
		return (1);
	}
	if (!info->check.sph)
		info->scene.spheres = ft_lstnew(sph);
	else
		ft_lstadd_back(&info->scene.spheres, ft_lstnew(sph));
	*list = info->scene.spheres;
	while ((*list)->next != NULL)
		*list = (*list)->next;
	return (0);
}

int	init_plane(t_minirt	*info, t_list	**list)
{
	t_light_point	*pln;

	pln = malloc(sizeof(t_plane) * 1);
	if (!pln)
	{
		info->info_error = 6;
		return (1);
	}
	if (!info->check.pln)
		info->scene.planes = ft_lstnew(pln);
	else
		ft_lstadd_back(&info->scene.planes, ft_lstnew(pln));
	*list = info->scene.planes;
	while ((*list)->next != NULL)
		*list = (*list)->next;
	return (0);
}

int	init_cylinder(t_minirt	*info, t_list	**list)
{
	t_light_point	*cyl;

	cyl = malloc(sizeof(t_cylinder) * 1);
	if (!cyl)
	{
		info->info_error = 6;
		return (1);
	}
	if (!info->check.cyl)
		info->scene.cylinders = ft_lstnew(cyl);
	else
		ft_lstadd_back(&info->scene.cylinders, ft_lstnew(cyl));
	*list = info->scene.cylinders;
	while ((*list)->next != NULL)
		*list = (*list)->next;
	return (0);
}
