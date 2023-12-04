/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:20:35 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/20 09:05:33 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	a;
	int		i;
	int		j;

	a = (char)c;
	i = ft_strlen(s);
	j = 0;
	while (j < i + 1)
	{
		if (s[j] == a)
		{
			return ((char *)s + j);
		}
		j++;
	}
	return (0);
}
