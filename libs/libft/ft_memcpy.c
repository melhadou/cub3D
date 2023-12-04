/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 12:36:36 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/19 18:27:36 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t_src;
	unsigned char	*t_dst;

	t_src = (unsigned char *)src;
	t_dst = (unsigned char *)dst;
	i = 0;
	if (n == 0 || (t_dst == 0 && t_src == 0))
		return (dst);
	while (i < n)
	{
		t_dst[i] = t_src[i];
		i++;
	}
	return (t_dst);
}
