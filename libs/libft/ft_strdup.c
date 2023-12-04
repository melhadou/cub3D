/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:40:57 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/19 19:12:17 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		len;

	ret = NULL;
	len = ft_strlen(s);
	ret = malloc(len + 1);
	if (!ret)
		return (ret);
	if (ret)
	{
		while (*s)
		{
			*ret = *s;
			ret++;
			s++;
		}
		*ret = '\0';
	}
	return (ret - len);
}
