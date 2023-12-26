/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:13:45 by melhadou          #+#    #+#             */
/*   Updated: 2023/06/22 08:25:17 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (*str);
}

int	gt_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	find_char_pos(char *s, int c)
{
	char	a;
	int		i;
	int		j;

	if (!s)
		return (0);
	if (s[0] == '\n')
		return (1);
	a = (char )c;
	i = gt_strlen(s);
	j = 0;
	while (j < i + 1)
	{
		if (s[j] == a)
			return (++j);
		j++;
	}
	return (0);
}

void	ft_cpy(char *str, const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j])
		{
			str[i + j] = s2[j];
			j++;
		}
	}
	str[i + j] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	len = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len += gt_strlen(s1);
	if (s2)
		len += gt_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	ft_cpy(str, s1, s2);
	return (str);
}
