/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 18:00:13 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/19 18:57:31 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*t_src;
	unsigned char	*t_dst;

	t_src = (unsigned char *) src;
	t_dst = (unsigned char *) dst;
	if (t_dst == 0 && t_src == 0)
		return (t_dst);
	if (t_src > t_dst)
		ft_memcpy(t_dst, t_src, len);
	else
	{
		while (0 < len)
		{
			t_dst[len - 1] = t_src[len - 1];
			len--;
		}
	}
	return (t_dst);
}
