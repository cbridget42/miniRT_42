/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:44 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/03 16:32:55 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rayTracing(t_minirt *data)
{
	int				x;
	int				y;
	t_coordinates	viewport;
	unsigned int	color;

	x = WIDTH / 2 * -1;
	while (x < WIDTH / 2)
	{
		y = HIGHT / 2;
		while (y > HIGHT / 2 * -1)
		{
			canvasToViewport(data, &viewport, x, y);
			color = traceRay(data, &viewport, 1.0f, __FLT_MAX__);
			my_mlx_pixel_put(&data->mlx, WIDTH / 2 + x, HIGHT / 2 - y, color);
			y--;
		}
		x++;
	}
}

void	canvasToViewport(t_minirt *data, t_coordinates *vp, float x, float y)
{
	vp->x = x * data->scene.viewport_width / WIDTH;
	vp->y = y * data->scene.viewport_hight / HIGHT;
	vp->z = data->scene.projection_plane_d;
}
