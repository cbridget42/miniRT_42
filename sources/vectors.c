/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:46:32 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/10 16:49:07 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coordinates	vectorSubtraction(t_coordinates *a, t_coordinates *b)
{
	t_coordinates	res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	return (res);
}

t_coordinates	vectorAddition(t_coordinates *a, t_coordinates *b)
{
	t_coordinates	res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	return (res);
}

t_coordinates	multiplicationScalar(t_coordinates *x, float s)
{
	t_coordinates	res;

	res.x = x->x * s;
	res.y = x->y * s;
	res.z = x->z * s;
	return (res);
}

float	dotVectors(t_coordinates *a, t_coordinates *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}

t_coordinates	cross_vectors(t_coordinates *a, t_coordinates *b)
{
	t_coordinates	res;

	res.x = (a->y * b->z) - (a->z * b->y);
	res.y = (a->z * b->x) - (a->x * b->z);
	res.z = (a->x * b->y) - (a->y * b->x);
	return (res);
}

float	vectorLength(t_coordinates *x)
{
	return (sqrtf((x->x * x->x) + (x->y * x->y) + (x->z * x->z)));
}

t_coordinates	vectorNarmolization(t_coordinates *x)
{
	t_coordinates	res;
	float			len;

	len = vectorLength(x);
	res.x = x->x / len;
	res.y = x->y / len;
	res.z = x->z / len;
	return (res);
}
