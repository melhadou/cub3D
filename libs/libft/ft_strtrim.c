/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:44:48 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/20 16:27:09 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	if (!set)
		return (ft_strdup(""));
	if (!s1)
		return (NULL);
	if (!s1[0])
		return (ft_strdup(""));
	len = ft_strlen(s1) - 1;
	while (ft_strchr((char *) set, *(s1 + i)))
		i++;
	while (ft_strchr((char *) set, *(s1 + len)))
		len--;
	trimed_str = ft_substr(s1, i, len - i + 1);
	if (!trimed_str)
		return (trimed_str);
	return (trimed_str);
}
