/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:29:40 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/02 14:48:27 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(void)
{
	t_minirt	data;

	init_rt(&data);

//	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);


	mlx_key_hook(data.mlx.mlx_win, select_keycode, &data);
	mlx_hook(data.mlx.mlx_win,  17, 0L, ft_close, &data);
	mlx_loop(data.mlx.mlx);

	return (0);
}
