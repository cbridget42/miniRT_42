/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:46:32 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/03 14:17:01 by cbridget         ###   ########.fr       */
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

float	dotVectors(t_coordinates *a, t_coordinates *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}
