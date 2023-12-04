/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:44:58 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/20 16:29:59 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wc(char const *s, char c)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		while (*(s + i) && *(s + i) != c)
			i++;
		if (*(s + i - 1) != c)
			ret++;
	}
	return (ret);
}

static	char	**ft_free(char **s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
	{
		free(*(s + i));
		i++;
	}
	free(s);
	return (NULL);
}

static	char	**ft_alloc(char *s, char c, char **ret)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[j])
		{
			ret[k] = ft_substr(s, j, i - j);
			if (!ret[k++])
				return (ft_free(ret));
		}
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = ft_calloc(ft_wc(s, c) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	ret = ft_alloc((char *)s, c, ret);
	return (ret);
}
