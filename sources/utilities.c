/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:43:42 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/13 19:35:43 by cbridget         ###   ########.fr       */
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
	red = checkChannel(red);
	green = checkChannel(green);
	blue = checkChannel(blue);
	return (create_trgb(red, green, blue));
}

unsigned int	add_colors(unsigned int c1, unsigned int c2)
{
	unsigned int	res;
	
	res = 0;
	res |= (unsigned int)checkChannel(((c1 & 0x00FF0000) >> 16) + ((c2 & 0x00FF0000) >> 16)) << 16;
	res |= (unsigned int)checkChannel(((c1 & 0x0000FF00) >> 8) + ((c2 & 0x0000FF00) >> 8)) << 8;
	res |= (unsigned int)checkChannel((c1 & 0x000000FF) + (c2 & 0x000000FF));
	return (res);
}

/*t_coordinates	create_vector(float x, float y, float z)
{
	t_coordinates	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}*/

float	checkChannel(float canal)
{
	if (canal < 0.0f)
		return (0.0f);
	else if (canal > 255.0f)
		return (255.0f);
	return (canal);
}

void	del(void *d)
{
	if (d)
		free(d);
}
