/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:43:42 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/04 15:36:21 by cbridget         ###   ########.fr       */
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

unsigned int	multiplicationColorByConstant(unsigned int color, float c)
{
	float	red;
	float	green;
	float	blue;

	red = (float)((color & 0x00FF0000) >> 16) * c;
	green = (float)((color & 0x0000FF00) >> 8) * c;
	blue = (float)(color & 0x000000FF) * c;
	red = checkCanal(red);
	green = checkCanal(green);
	blue = checkCanal(blue);
	return (create_trgb(red, green, blue));
}

float	checkCanal(float canal)
{
	if (canal < 0)
		return (0.0f);
	else if (canal > 255)
		return (255.0f);
	return (canal);
}

void	del(void *d)
{
	if (d)
		free(d);
}
