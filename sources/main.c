/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:29:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/09/30 14:45:50 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_square(t_data *mlx, int x, int y, int color);

int	main(void)
{
	t_data	mlx;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HIGHT, "miniRT");
	mlx.img = mlx_new_image(mlx.mlx, WIDTH, HIGHT);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, &mlx.endian);
	draw_square(&mlx, 150, 100, 0x00FF0000);
	draw_square(&mlx, 350, 100, 0x0000FF00);
	draw_square(&mlx, 250, 300, 0x000000FF);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);

	return (0);
}

void	draw_square(t_data *mlx, int x, int y, int color)
{
	int	s_x;
	int	s_y;

	s_y = y;
	y += 200;
	while (s_y < y)
	{
		s_x = x;
		while (s_x < x + 200)
		{
			my_mlx_pixel_put(mlx, s_x, s_y, color);
			s_x++;
		}
		s_y++;
	}
}
