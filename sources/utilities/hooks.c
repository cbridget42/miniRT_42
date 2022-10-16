/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:18:29 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/16 18:34:01 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	select_keycode(int keycode, t_minirt *data)
{
	if (keycode == ESC)
		ft_close(data);
	return (0);
}

int	ft_close(t_minirt *data)
{
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	ft_lstclear(&data->scene.spheres, del);
	ft_lstclear(&data->scene.planes, del);
	ft_lstclear(&data->scene.cylinders, del);
	ft_lstclear(&data->light_p, del);
	exit(0);
}
