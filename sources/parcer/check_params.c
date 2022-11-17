/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 07:56:13 by ymirna            #+#    #+#             */
/*   Updated: 2022/10/26 19:52:24 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	correct_chars(char	*arr, int x)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (x == 0)
		{
			if (!ft_isdigit(arr[i]) && is_char(arr[i], '.')
				&& is_char(arr[i], ',') && is_char(arr[i], '-'))
				return (1);
		}
		else if (x == 1)
		{
			if (!ft_isdigit(arr[i]) && is_char(arr[i], '.'))
				return (1);
		}
		else if (x == 2)
		{
			if (!ft_isdigit(arr[i]) && is_char(arr[i], ','))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_info_x(char	**arr, int x)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	if ((i == 2 && (x == 0 || x == 2)) || (i == 3
			&& (x == 1 || x == 3 || x == 4)) || (i == 5 && x == 5))
	{
		i = 0;
		while (arr[i])
		{
			if (correct_chars(arr[i], 0))
				return (4);
			i++;
		}
		return (0);
	}
	return (4);
}
