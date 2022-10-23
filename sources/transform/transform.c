/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:30:32 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 17:56:08 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_obj_x(t_minirt *data, char sign)
{
	int	cam_flag;

	cam_flag = 0;
	if (data->transform_flag == CAM && !data->norm_flag)
		conf_axis(data, &((t_camera *)data->transform_obj)->orig.x, sign);
	else if (data->transform_flag == CAM && data->norm_flag)
	{
		conf_axis(data, &((t_camera *)data->transform_obj)->normal.x, sign);
		cam_flag = 1;
	}
	else if (data->transform_flag == LIGHT && !data->norm_flag)
		conf_axis(data, &((t_light_point *)data->transform_obj)->coord.x, sign);
	else if (data->transform_flag == SPHERE && !data->norm_flag)
		conf_axis(data, &((t_sphere *)data->transform_obj)->center.x, sign);
	else if (data->transform_flag == PLANE && !data->norm_flag)
		conf_axis(data, &((t_plane *)data->transform_obj)->center.x, sign);
	else if (data->transform_flag == PLANE && data->norm_flag)
		conf_axis(data, &((t_plane *)data->transform_obj)->normal.x, sign);
	else if (data->transform_flag == CYLINDER && !data->norm_flag)
		conf_axis(data, &((t_cylinder *)data->transform_obj)->center.x, sign);
	else if (data->transform_flag == CYLINDER && data->norm_flag)
		conf_axis(data, &((t_cylinder *)data->transform_obj)->normal.x, sign);
	rerender(data, cam_flag);
}

void	select_obj_y(t_minirt *data, char sign)
{
	int	cam_flag;

	cam_flag = 0;
	if (data->transform_flag == CAM && !data->norm_flag)
		conf_axis(data, &((t_camera *)data->transform_obj)->orig.y, sign);
	else if (data->transform_flag == CAM && data->norm_flag)
	{
		conf_axis(data, &((t_camera *)data->transform_obj)->normal.y, sign);
		cam_flag = 1;
	}
	else if (data->transform_flag == LIGHT && !data->norm_flag)
		conf_axis(data, &((t_light_point *)data->transform_obj)->coord.y, sign);
	else if (data->transform_flag == SPHERE && !data->norm_flag)
		conf_axis(data, &((t_sphere *)data->transform_obj)->center.y, sign);
	else if (data->transform_flag == PLANE && !data->norm_flag)
		conf_axis(data, &((t_plane *)data->transform_obj)->center.y, sign);
	else if (data->transform_flag == PLANE && data->norm_flag)
		conf_axis(data, &((t_plane *)data->transform_obj)->normal.y, sign);
	else if (data->transform_flag == CYLINDER && !data->norm_flag)
		conf_axis(data, &((t_cylinder *)data->transform_obj)->center.y, sign);
	else if (data->transform_flag == CYLINDER && data->norm_flag)
		conf_axis(data, &((t_cylinder *)data->transform_obj)->normal.y, sign);
	rerender(data, cam_flag);
}

void	select_obj_z(t_minirt *data, char sign)
{
	int	cam_flag;

	cam_flag = 0;
	if (data->transform_flag == CAM && !data->norm_flag)
		conf_axis(data, &((t_camera *)data->transform_obj)->orig.z, sign);
	else if (data->transform_flag == CAM && data->norm_flag)
	{
		conf_axis(data, &((t_camera *)data->transform_obj)->normal.z, sign);
		cam_flag = 1;
	}
	else if (data->transform_flag == LIGHT && !data->norm_flag)
		conf_axis(data, &((t_light_point *)data->transform_obj)->coord.z, sign);
	else if (data->transform_flag == SPHERE && !data->norm_flag)
		conf_axis(data, &((t_sphere *)data->transform_obj)->center.z, sign);
	else if (data->transform_flag == PLANE && !data->norm_flag)
		conf_axis(data, &((t_plane *)data->transform_obj)->center.z, sign);
	else if (data->transform_flag == PLANE && data->norm_flag)
		conf_axis(data, &((t_plane *)data->transform_obj)->normal.z, sign);
	else if (data->transform_flag == CYLINDER && !data->norm_flag)
		conf_axis(data, &((t_cylinder *)data->transform_obj)->center.z, sign);
	else if (data->transform_flag == CYLINDER && data->norm_flag)
		conf_axis(data, &((t_cylinder *)data->transform_obj)->normal.z, sign);
	rerender(data, cam_flag);
}

void	conf_axis(t_minirt *data, float *axis, char sign)
{
	if (sign == '+')
	{
		if (data->norm_flag)
			*axis += 0.1;
		else
			*axis += 1.0;
	}
	else
	{
		if (data->norm_flag)
			*axis -= 0.1;
		else
			*axis -= 1.0;
	}
}

void	rerender(t_minirt *data, int flag)
{
	void	*img_tmp;

	img_tmp = data->mlx.img;
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, \
	&data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
	if (flag)
		config_cam(data, 0);
	ray_tracing(data);
	mlx_destroy_image(data->mlx.mlx, img_tmp);
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
	data->mlx.img, 0, 0);
}
