/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbridget <cbridget@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 18:25:38 by cbridget          #+#    #+#             */
/*   Updated: 2022/10/16 14:08:56 by cbridget         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	err;

	if (s)
	{
		while (*s)
		{
			err = write(fd, s, 1);
			s++;
		}
		err = write(fd, "\n", 1);
	}
	if (err == -1)
		(void)err;
}
