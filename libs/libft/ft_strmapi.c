/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:45:30 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/12 21:10:20 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*ret;

	ret = NULL;
	i = 0;
	if (!s || !f)
		return (ret);
	len = ft_strlen(s);
	ret = ft_calloc(len + 1, 1);
	if (!ret)
		return (ret);
	while (*(s + i))
	{
		*(ret + i) = f(i, *(s + i));
		i++;
	}
	return (ret);
}
