/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:02:06 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/16 19:40:39 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*t_s;
	unsigned char	t_c;
	size_t			i;

	t_s = (unsigned char *)s;
	t_c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (t_s[i] == t_c)
			return ((t_s + i));
		i++;
	}
	return (NULL);
}
