/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:37:09 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/15 23:24:14 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vector_length(t_coords *x)
{
	return (sqrtf((x->x * x->x) + (x->y * x->y) + (x->z * x->z)));
}

t_coords	vector_narmolization(t_coords *x)
{
	t_coords	res;
	float			len;

	len = vector_length(x);
	res.x = x->x / len;
	res.y = x->y / len;
	res.z = x->z / len;
	return (res);
}
