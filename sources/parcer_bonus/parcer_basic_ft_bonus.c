/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_basic_ft_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:03:56 by ymirna            #+#    #+#             */
/*   Updated: 2022/10/26 17:20:12 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	char_value(char	*str, char c, int x, int less)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == c)
			y++;
		i++;
	}
	if (x == y && less == 0)
		return (0);
	else if (x >= y && less == 1)
		return (0);
	return (1);
}

int	is_char(char a, char b)
{
	if (a != b)
		return (1);
	return (0);
}

int	if_char(t_minirt	*info, char a, char b)
{
	if (a != b)
	{
		info->info_error = 4;
		return (1);
	}
	return (0);
}

int	if_str_arr(t_minirt	*info, char	**arr, int x)
{
	if (!arr || !arr[0])
	{
		info->info_error = 6;
		return (6);
	}
	info->str_arr = arr;
	return (check_info_x(arr, x));
}

int	ft_strn_ncmp(char	*s1, char	*s2, size_t start, size_t n)
{
	size_t			i;
	size_t			y;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = start;
	y = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (i < n && (ss1[i] || ss2[y]))
	{
		if (ss1[i] == s2[y])
		{
			i++;
			y++;
		}
		else
			return (ss1[i] - ss2[y]);
	}
	return (0);
}
