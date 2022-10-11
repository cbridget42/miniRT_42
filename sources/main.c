/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:29:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/11 14:22:15 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void pseudoParser(t_minirt *data);

int	main(void)
{
	t_minirt	data;

	init_rt(&data);
	pseudoParser(&data);

	config_cam(&data);
	rayTracing(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.mlx_win, data.mlx.img, 0, 0);

	mlx_key_hook(data.mlx.mlx_win, select_keycode, &data);
	mlx_hook(data.mlx.mlx_win,  17, 0L, ft_close, &data);
	mlx_loop(data.mlx.mlx);

	return (0);
}

void pseudoParser(t_minirt *data)
{
	data->scene.viewport_hight = tan(100.0f / 2.0f * (M_PI / 180)) * 2;
	data->scene.viewport_width = tan(100.0f / 2.0f * (M_PI / 180)) * 2;

	data->light_a.intensity = 0.2f;

	t_light_point *light_p = malloc(sizeof(t_light_point) * 1);
	light_p->crdn.x = 7;
	light_p->crdn.y = 7;
	light_p->crdn.z = 1;
	light_p->intensity = 0.6f;
	data->light_p = ft_lstnew(light_p);
	light_p = malloc(sizeof(t_light_point) * 1);
	light_p->crdn.x = -7;
	light_p->crdn.y = 7;
	light_p->crdn.z = 1;
	light_p->intensity = 0.4f;
	ft_lstadd_back(&data->light_p, ft_lstnew(light_p));

	t_sphere *sphere1 = malloc(sizeof(t_sphere) * 1);
	sphere1->center.x = 0;
	sphere1->center.y = 3;
	sphere1->center.z = 7;
	sphere1->radius = 2.5;
	sphere1->color = create_trgb(255, 0, 0);
	data->scene.spheres = ft_lstnew(sphere1);
	sphere1 = malloc(sizeof(t_sphere) * 1);
	sphere1->center.x = 1.5;
	sphere1->center.y = 0;
	sphere1->center.z = 3;
	sphere1->radius = 1;
	sphere1->color = create_trgb(255, 0, 255);
	ft_lstadd_back(&(data->scene.spheres), ft_lstnew(sphere1));
	sphere1 = malloc(sizeof(t_sphere) * 1);
	sphere1->center.x = -2;
	sphere1->center.y = 0;
	sphere1->center.z = 4;
	sphere1->radius = 1;
	sphere1->color = create_trgb(0, 255, 0);
	ft_lstadd_back(&(data->scene.spheres), ft_lstnew(sphere1));
/*	sphere1 = malloc(sizeof(t_sphere) * 1);
	sphere1->center.x = 0;
	sphere1->center.y = -5001;
	sphere1->center.z = 0;
	sphere1->radius = 5000;
	sphere1->color = create_trgb(255, 255, 0);
	ft_lstadd_back(&(data->scene.spheres), ft_lstnew(sphere1));*/

	t_plane *plane = malloc(sizeof(t_plane) * 1);
	plane->center.x = 0;
	plane->center.y = 0;
	plane->center.z = 10;
	plane->normal.x = 0;
	plane->normal.y = 0;
	plane->normal.z = -1;
	plane->color = create_trgb(255, 255, 255);
	data->scene.planes = ft_lstnew(plane);
	plane = malloc(sizeof(t_plane) * 1);
	plane->center.x = 0;
	plane->center.y = -1;
	plane->center.z = 0;
	plane->normal.x = 0;
	plane->normal.y = -1;
	plane->normal.z = 0;
	plane->color = create_trgb(255, 0, 255);
	ft_lstadd_back(&data->scene.planes, ft_lstnew(plane));

	data->camera.orig.x = 0;
	data->camera.orig.y = 0;
	data->camera.orig.z = 0;
	data->camera.normal.x = 0;
	data->camera.normal.y = 0;
	data->camera.normal.z = 1;
	data->camera.fov = 120.0f;
}
