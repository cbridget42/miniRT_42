/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:43:42 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/03 16:09:29 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	*(unsigned int*)(mlx->addr + (y * mlx->line_length + x \
	* (mlx->bits_per_pixel / 8))) = color;
}

unsigned int	create_trgb(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char	t;

	t = 0;
	return (*(unsigned int *)(unsigned char [4]){b, g, r, t});
}

void	del(void *d)
{
	if (d)
		free(d);
}
