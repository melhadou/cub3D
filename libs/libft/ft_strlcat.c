/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:25:41 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/19 18:33:41 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_len;
	size_t	d_len;
	size_t	i;
	size_t	j;

	s_len = ft_strlen((char *)src);
	if (size == 0)
		return (s_len);
	d_len = ft_strlen(dst);
	if (d_len < size)
	{
		j = d_len;
		i = 0;
		while (*(src + i) != '\0' && i < size - d_len - 1)
		{
			*(dst + j) = *(src + i);
			i++;
			j++;
		}
		*(dst + j) = '\0';
		return (d_len + s_len);
	}
	return (size + s_len);
}
