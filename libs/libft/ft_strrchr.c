/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:50:28 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/20 09:01:42 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	tmp;
	int		i;

	i = 0;
	tmp = (char)c;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == tmp)
		{
			return ((char *)s + i);
		}
		i--;
	}
	return (NULL);
}
