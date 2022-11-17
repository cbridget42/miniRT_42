/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_info_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 01:55:05 by ymirna            #+#    #+#             */
/*   Updated: 2022/10/26 18:18:09 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static char	**fill_coord_free(t_minirt	*info, char	**str_arr)
{
	free_str_arr(str_arr);
	info->info_error = 4;
	return (NULL);
}

static char	**fill_coord_split(t_minirt	*info, char	*str, int i)
{
	char	**str_arr;

	str_arr = ft_split(str, ',');
	if (!str_arr)
	{
		info->info_error = 6;
		return (NULL);
	}
	while (str_arr[i])
	{
		if (char_value(str_arr[i], '.', 1, 1)
			|| char_value(str_arr[i], '-', 1, 1))
			return (fill_coord_free(info, str_arr));
		i++;
	}
	if (i != 3)
		return (fill_coord_free(info, str_arr));
	return (str_arr);
}

static void	fill_coord_value(t_coords	*coord, char	**str_arr, int	*norm)
{
	coord->x = ft_atof(str_arr[0]);
	coord->y = ft_atof(str_arr[1]);
	coord->z = ft_atof(str_arr[2]);
	if (*norm)
	{
		if ((-1.0 <= coord->x && coord->x <= 1.0) && (-1.0 <= coord->y
				&& coord->y <= 1.0) && (-1.0 <= coord->z && coord->z <= 1.0))
			*norm = 0;
	}
}

void	fill_coord(t_minirt	*info, t_coords	*coord, char	*str, int norm)
{
	char	**str_arr;
	int		i;

	if (info->info_error)
		return ;
	if (char_value(str, '.', 3, 1) || char_value(str, ',', 2, 0)
		|| correct_chars(str, 0))
	{
		info->info_error = 4;
		return ;
	}
	i = 0;
	str_arr = fill_coord_split(info, str, i);
	if (info->info_error)
		return ;
	fill_coord_value(coord, str_arr, &norm);
	if (norm)
		info->info_error = 4;
	free_str_arr(str_arr);
}
