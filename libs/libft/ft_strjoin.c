/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:44:37 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/02 18:42:15 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*a;

// 	if (!s1)
// 	{
// 		s1 = malloc(sizeof(char));
// 		if (!s1)
// 			return (NULL);
// 		s1[0] = '\0';
// 	}
// 	i = -1;
// 	j = -1;
// 	a = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (!a)
// 		return (NULL);
// 	while (s1[++i])
// 		a[i] = s1[i];
// 	while (s2[++j])
// 		a[i + j] = s2[j];
// 	a[i + j] = '\0';
// 	free(s1);
// 	return (a);
// }
