/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:20:35 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/02 18:27:47 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (str[i] != (char) c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (str + i);
}
