/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:05:42 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/19 18:19:04 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*t_mem;

	t_mem = NULL;
	if (size && nmemb >= SIZE_MAX / size)
		return (NULL);
	t_mem = malloc(size * nmemb);
	if (t_mem == NULL)
		return (t_mem);
	ft_bzero(t_mem, (size * nmemb));
	return (t_mem);
}
