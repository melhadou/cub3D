/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:44:29 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/02 18:29:41 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, size_t start, size_t end)
{
	char	*str;
	int		i;

	if (start > end)
		return (NULL);
	str = malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
