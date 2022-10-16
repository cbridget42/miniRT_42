/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:43:42 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/16 18:33:16 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

unsigned int	multiplication_color_constant(unsigned int color, float c)
{
	float	red;
	float	green;
	float	blue;

	red = (float)((color & 0x00FF0000) >> 16) *c;
	green = (float)((color & 0x0000FF00) >> 8) *c;
	blue = (float)(color & 0x000000FF) *c;
	red = check_channel(red);
	green = check_channel(green);
	blue = check_channel(blue);
	return (create_trgb(red, green, blue));
}

unsigned int	add_colors(unsigned int c1, unsigned int c2)
{
	unsigned int	res;

	res = 0;
	res |= (unsigned int)check_channel(((c1 & 0x00FF0000) >> 16) \
			+ ((c2 & 0x00FF0000) >> 16)) << 16;
	res |= (unsigned int)check_channel(((c1 & 0x0000FF00) >> 8) \
			+ ((c2 & 0x0000FF00) >> 8)) << 8;
	res |= (unsigned int)check_channel((c1 & 0x000000FF) + (c2 & 0x000000FF));
	return (res);
}

float	check_channel(float canal)
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
