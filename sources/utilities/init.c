/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:37:06 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 16:49:11 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_rt(t_minirt *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIDTH, HIGHT, "miniRT");
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, \
	&data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	data->norm_flag = 0;
	data->transform_flag = CAM;
	data->transform_obj = &data->camera;
}
