/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:45:11 by melhadou          #+#    #+#             */
/*   Updated: 2022/11/12 21:14:07 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ret;

	len = 0;
	if (!n)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = nlen(n);
	ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	*(ret + len--) = '\0';
	if (n < 0)
	{
		*(ret) = '-';
		n = n * -1;
	}
	while (n)
	{
		*(ret + len--) = n % 10 + '0';
		n = n / 10;
	}
	return (ret);
}
