/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:44:37 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/12 21:09:56 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_cpy(char const *s1, char const *s2, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(s1 + i))
	{
		*(str + j) = *(s1 + i);
		j++;
		i++;
	}
	i = 0;
	while (*(s2 + i))
	{
		*(str + j) = *(s2 + i);
		j++;
		i++;
	}
	*(str + j) = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	s2_len = 0;
	str = NULL;
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2)
		s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (str);
	ft_cpy(s1, s2, str);
	return (str);
}
