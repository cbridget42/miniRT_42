/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersectRaySphere.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:40:23 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/04 18:17:52 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersectRaySphere(t_coordinates *c, t_coordinates *viewport, t_sphere *sphere, t_answer *asw)
{
	t_coordinates	x;
	float			k1;
	float			k2;
	float			k3;
	float			discriminant;

	x = vectorSubtraction(c, &sphere->center);
	k1 = dotVectors(viewport, viewport);
	k2 = 2.0f * dotVectors(&x, viewport);
	k3 = dotVectors(&x, &x) - (sphere->radius * sphere->radius);
	discriminant = (k2 * k2) - (4 * k1 * k3);
	if (discriminant < 0)
	{
		asw->t1 = __FLT_MAX__;
		asw->t2 = __FLT_MAX__;
		return;
	}
	asw->t1 = (-k2 + sqrt(discriminant)) / (2 * k1);
	asw->t2 = (-k2 - sqrt(discriminant)) / (2 * k1);
}
