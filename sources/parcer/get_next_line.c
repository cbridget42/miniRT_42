/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:21:54 by ymirna            #+#    #+#             */
/*   Updated: 2022/10/26 17:21:37 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minirt.h"

static int	ft_check(char	*buf, t_gnl	*st)
{
	st->i = 0;
	while (buf[st->i])
	{
		if (buf[st->i] == '\n')
		{
			if (st->i + 1 == ft_strlen(buf))
				return (1);
			else
				return (2);
		}
		st->i++;
	}
	return (0);
}

static char	*ft_chop(char	*str1, char	*end, t_gnl	*st)
{
	int		x;

	st->str = NULL;
	x = ft_check(end, st);
	if (x > 0)
	{
		if (x == 1)
			str1 = ft_sub(end, 0, st->i + 1, 1);
		if (x == 2)
		{
			str1 = ft_sub(end, 0, st->i + 1, 0);
			st->str = ft_sub(end, st->i + 1,
					ft_strlen(end) - st->i, 1);
		}
		st->line = 0;
	}
	else
		str1 = ft_join(str1, end, 1);
	return (str1);
}

static char	*ft_work(char	*buf, char **str1, char	*end, t_gnl	*st)
{
	while (st->chr && st->line)
	{
		st->chr = read(st->fd, buf, 1);
		buf[st->chr] = '\0';
		if (!ft_strlen(buf) || !st->chr)
			break ;
		if (ft_check(buf, st) == 2)
		{
			*str1 = ft_join(*str1, ft_sub(buf, 0, st->i + 1, 0), 1);
			end = ft_sub(buf, st->i + 1, ft_strlen(buf) - st->i, 0);
		}
		else if (!end)
			*str1 = ft_join(*str1, buf, 0);
		if (buf[st->i] == '\n')
			break ;
	}
	return (end);
}

static void	fill_gnl(t_gnl	*stc, int fd)
{
	stc->chr = 1;
	stc->line = 1;
	stc->fd = fd;
}

int	get_next_line(char	**ret, int fd)
{
	t_gnl		stc;
	char		buf[2];
	static char	*end;
	char		*str1;

	if (read(fd, NULL, 0) < 0)
		return (4);
	str1 = NULL;
	fill_gnl(&stc, fd);
	if (end)
	{
		str1 = ft_chop(str1, end, &stc);
		end = stc.str;
	}
	end = ft_work(buf, &str1, end, &stc);
	if (ft_strlen(str1) == 1)
	{
		free(str1);
		return (1);
	}
	else if (!str1 || ft_strlen(str1) == 0)
		return (2);
	else
		ft_trim(ret, str1);
	return (0);
}
