/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 18:30:26 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/20 19:29:32 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_coords	reflect_ray(t_coords *norm, t_coords *ray)
{
	t_coords	reflect;

	reflect = multiplication_scalar(norm, dot_vectors(norm, ray) * 2);
	reflect = vector_subtraction(&reflect, ray);
	return (reflect);
}
