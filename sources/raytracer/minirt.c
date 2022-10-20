/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:44 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/19 17:49:56 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ray_tracing(t_minirt *data)
{
	int				x;
	int				y;
	t_ray			ray;
	unsigned int	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HIGHT)
		{
			make_dir(data, &ray.dir, (float)x * 2 / WIDTH - 1, \
					(float)y * 2 / HIGHT - 1);
			ray.orig = data->camera.orig;
			color = trace_ray(data, &ray, 1.0f, DEPTH);
			my_mlx_pixel_put(&data->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	make_dir(t_minirt *data, t_coords *dir, float x, float y)
{
	t_coords	tmp_a;
	t_coords	tmp_b;

	tmp_a = multiplication_scalar(&data->camera.y, \
				data->scene.viewport_hight * x);
	tmp_b = multiplication_scalar(&data->camera.x, \
				data->scene.viewport_width * y);
	tmp_a = vector_addition(&tmp_a, &tmp_b);
	*dir = vector_addition(&tmp_a, &data->camera.z);
	*dir = vector_narmolization(dir);
}

void	config_cam(t_minirt *data)
{
	t_coords	tmp;
	float		x;

	tmp.x = 0.0f;
	tmp.y = 1.0f;
	tmp.z = 0.0f;
	x = (float)HIGHT / WIDTH;
	data->camera.normal = vector_narmolization(&data->camera.normal);
	data->scene.viewport_hight = tanf(data->camera.fov / 2.0f * (M_PI / 180));
	data->scene.viewport_width = data->scene.viewport_hight * x;
	data->camera.z = data->camera.normal;
	tmp = cross_vectors(&data->camera.z, &tmp);
	data->camera.y = vector_narmolization(&tmp);
	data->camera.x = cross_vectors(&data->camera.z, &data->camera.y);
	data->camera.x = vector_narmolization(&data->camera.x);
}
