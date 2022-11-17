/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymirna <ymirna@student.21-school.>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 20:59:14 by ymirna            #+#    #+#             */
/*   Updated: 2021/10/26 20:20:14 by ymirna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static size_t	ft_words(char const	*s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
				i++;
			j++;
		}
	}
	return (j);
}

static void	ft_freeall(char **sttr, size_t	words)
{
	size_t	i;

	i = 0;
	while (i < words)
	{
		free(sttr[i]);
		i++;
	}
	free(sttr);
}

static char	**ft_strprs(char	**sttr, char const	*s, char c, size_t	words)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	while (j < words && s[i])
	{
		len = 0;
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i])
			{
				len++;
				i++;
			}
			sttr[j] = ft_substr(s, i - len, len);
			if (!sttr)
				ft_freeall(sttr, j);
			j++;
		}
	}
	return (sttr);
}

char	**ft_split(char const	*s, char c)
{
	char	**sttr;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	sttr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!sttr)
		return (NULL);
	sttr = ft_strprs(sttr, s, c, words);
	if (!sttr)
		return (NULL);
	sttr[words] = NULL;
	return (sttr);
}
