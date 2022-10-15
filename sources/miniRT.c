/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:44 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/15 15:10:47 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rayTracing(t_minirt *data)
{
	int				x;
	int				y;
	t_coordinates	ray;
	unsigned int	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HIGHT)
		{
			make_ray(data, &ray, (float)x * 2 / WIDTH - 1, (float)y * 2 / HIGHT - 1);
			color = traceRay(data, &ray);
			my_mlx_pixel_put(&data->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	make_ray(t_minirt *data, t_coordinates *ray, float x, float y)
{
	t_coordinates	tmp_a;
	t_coordinates	tmp_b;

	tmp_a = multiplicationScalar(&data->camera.y, data->scene.viewport_hight * x);
	tmp_b = multiplicationScalar(&data->camera.x, data->scene.viewport_width * y);
	tmp_a = vectorAddition(&tmp_a, &tmp_b);
	*ray = vectorAddition(&tmp_a, &data->camera.z);
	*ray = vectorNarmolization(ray);
}

void	config_cam(t_minirt	*data)
{
	t_coordinates	tmp;
	float			x;

	tmp.x = 0.0f;
	tmp.y = 1.0f;
	tmp.z = 0.0f;
	x = (float)HIGHT / WIDTH;
	data->camera.normal = vectorNarmolization(&data->camera.normal);
	data->scene.viewport_hight = tanf(data->camera.fov / 2.0f * (M_PI / 180));
	data->scene.viewport_width = data->scene.viewport_hight * x;
	data->camera.z = data->camera.normal;
	tmp = cross_vectors(&data->camera.z, &tmp);
	data->camera.y = vectorNarmolization(&tmp);
	data->camera.x = cross_vectors(&data->camera.z, &data->camera.y);
	data->camera.x = vectorNarmolization(&data->camera.x);
}
