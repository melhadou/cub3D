/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:50:28 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/27 18:35:41 by uns-35           ###   ########.fr       */
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
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
