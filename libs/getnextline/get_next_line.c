/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:12:44 by melhadou          #+#    #+#             */
/*   Updated: 2023/06/24 20:22:35 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*loop(int fd, char *buf, char *line)
{
	int		tmp;
	int		r;
	char	*temp;

	while (1)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			ft_free(&buf);
			ft_free(&line);
			return (NULL);
		}
		buf[r] = '\0';
		temp = line;
		line = ft_strjoin(line, buf);
		ft_free(&temp);
		tmp = find_char_pos(buf, '\n');
		if (tmp || r == 0)
			break ;
	}
	ft_free(&buf);
	return (line);
}

char	*read_buffer(int fd)
{
	char	*buf;
	char	*line;

	buf = NULL;
	line = NULL;
	buf = malloc((sizeof(char ) * (BUFFER_SIZE + 1)));
	if (!buf)
		return (NULL);
	line = loop(fd, buf, line);
	return (line);
}

char	*get_bf_newline(char *line)
{
	int		n;
	int		i;
	char	*bf_newline;

	n = 0;
	i = -1;
	if (!line)
		return (NULL);
	n = find_char_pos(line, '\n');
	if (n == 0)
		n = gt_strlen(line);
	if (!n)
		return (NULL);
	bf_newline = malloc(sizeof(char) * (n));
	if (!bf_newline)
		return (NULL);
	n--;
	while (++i < n)
		bf_newline[i] = line[i];
	bf_newline[i] = '\0';
	return (bf_newline);
}

char	*get_af_newline(char *line)
{
	int		n;
	int		i;
	int		len;
	char	*af_newline;

	n = 0;
	len = 0;
	if (!line)
		return (NULL);
	n = find_char_pos(line, '\n');
	len = gt_strlen(line);
	if (!n)
		return (NULL);
	af_newline = malloc(sizeof(char) * (len - n + 1));
	if (!af_newline)
		return (NULL);
	i = -1;
	while (line[++i + n])
		af_newline[i] = line[n + i];
	af_newline[i] = '\0';
	return (af_newline);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*line;
	char		*buf;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!find_char_pos(backup, '\n'))
		buf = read_buffer(fd);
	else
	{
		buf = malloc(1);
		if (!buf)
			return (NULL);
		*buf = '\0';
	}
	if (!buf)
		return (ft_free(&backup));
	tmp = ft_strjoin(backup, buf);
	ft_free(&backup);
	ft_free(&buf);
	line = get_bf_newline(tmp);
	backup = get_af_newline(tmp);
	ft_free(&tmp);
	return (line);
}
