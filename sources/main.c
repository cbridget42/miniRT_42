/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:29:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/09/30 19:06:02 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	draw_square(t_data *mlx, int x, int y, int color);

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIDTH, HIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	draw_square(&data, 150, 100, 0x00FF0000);
	draw_square(&data, 350, 100, 0x0000FF00);
	draw_square(&data, 250, 300, 0x000000FF);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_key_hook(data.mlx_win, select_keycode, &data);
	mlx_hook(data.mlx_win,  17, 0L, ft_close, &data);
	mlx_loop(data.mlx);

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
