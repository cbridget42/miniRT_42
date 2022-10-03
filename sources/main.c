/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:29:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/03 15:56:25 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void pseudoParser(t_minirt *data);

int	main(void)
{
	t_minirt	data;

	init_rt(&data);
	pseudoParser(&data);

	rayTracing(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.mlx_win, data.mlx.img, 0, 0);

	mlx_key_hook(data.mlx.mlx_win, select_keycode, &data);
	mlx_hook(data.mlx.mlx_win,  17, 0L, ft_close, &data);
	mlx_loop(data.mlx.mlx);

	return (0);
}


void pseudoParser(t_minirt *data)
{
	data->scene.viewport_hight = 1;
	data->scene.viewport_width = 1;
	data->scene.projection_plane_d = 1;
	t_sphere *sphere1 = malloc(sizeof(t_sphere) * 1);
	sphere1->center.x = 0;
	sphere1->center.y = -1;
	sphere1->center.z = 3;
	sphere1->radius = 1;
	sphere1->color = create_trgb(255, 0, 0);
	data->scene.spheres = ft_lstnew(sphere1);
	sphere1 = malloc(sizeof(t_sphere) * 1);
	sphere1->center.x = 2;
	sphere1->center.y = 0;
	sphere1->center.z = 4;
	sphere1->radius = 1;
	sphere1->color = create_trgb(0, 0, 255);
	ft_lstadd_back(&(data->scene.spheres), ft_lstnew(sphere1));
	sphere1 = malloc(sizeof(t_sphere) * 1);
	sphere1->center.x = -2;
	sphere1->center.y = 0;
	sphere1->center.z = 4;
	sphere1->radius = 1;
	sphere1->color = create_trgb(0, 255, 0);
	ft_lstadd_back(&(data->scene.spheres), ft_lstnew(sphere1));

	data->camera.crdn.x = 0;
	data->camera.crdn.y = 0;
	data->camera.crdn.z = 0;
}
