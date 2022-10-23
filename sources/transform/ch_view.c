/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:55:13 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/23 17:55:35 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	change_review(t_minirt *data)
{
	if (data->norm_flag)
		data->norm_flag = 0;
	else
		data->norm_flag = 1;
}
