/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:18:29 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/26 17:38:55 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	select_keycode(int keycode, t_minirt *data)
{
	if (keycode == ESC)
		ft_close(data);
	else if (keycode == A)
		select_obj_x(data, '+');
	else if (keycode == D)
		select_obj_x(data, '-');
	else if (keycode == W)
		select_obj_z(data, '+');
	else if (keycode == S)
		select_obj_z(data, '-');
	else if (keycode == ARROW_UP)
		select_obj_y(data, '+');
	else if (keycode == ARROW_DOWN)
		select_obj_y(data, '-');
	else if (keycode == Q)
		change_review(data);
	else if (keycode == E)
		change_obj(data);
	return (select_keycode_two(keycode, data));
}

int	select_keycode_two(int keycode, t_minirt *data)
{
	if (keycode == Z)
		change_radius(data, '+');
	else if (keycode == X)
		change_radius(data, '-');
	else if (keycode == C)
		change_height(data, '+');
	else if (keycode == V)
		change_height(data, '-');
	return (0);
}

int	ft_close(t_minirt *data)
{
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	if (data->scene.spheres)
		ft_lstclear(&data->scene.spheres, del);
	if (data->scene.planes)
		ft_lstclear(&data->scene.planes, del);
	if (data->scene.cylinders)
		ft_lstclear(&data->scene.cylinders, del);
	if (data->light_p)
		ft_lstclear(&data->light_p, del);
	exit(0);
}
