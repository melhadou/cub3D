/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:18:09 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 01:42:00 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strrchr(char *s, int c);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *src);
// char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, size_t start, size_t end);
size_t	ft_strlen(char *str);
char	*ft_strtrim(char *s1, char *set);
char	*ft_strchr(char *s, int c);
char	**ft_split(char *s, char c);
int		ft_atoi(char *str);
int		ft_isdigit(int c);

#endif
