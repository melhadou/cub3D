/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:43:57 by yoelansa          #+#    #+#             */
/*   Updated: 2024/01/01 21:07:45 by uns-35           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_borders(t_parser	*data, int i, int j)
{
	int		len;
	char	**map;

	len = ft_strlen(data->map[i]);
	map = data->map;
	if (map[i][j] == '0' || map[i][j] == 'N'
		|| map[i][j] == 'E' || map[i][j] == 'W' || map[i][j] == 'S')
	{
		if (i == 0 || j == 0 || i == data->height - 1 || j == len - 1)
			return (ft_exit_error
				("Error : The map must be surrounded by walls (1)!"), 1);
		if (j > (int)ft_strlen(map[i - 1]) || j > (int)ft_strlen(map[i + 1]))
			return (ft_exit_error
				("Error : The map must be surrounded by walls (1)!"), 1);
		if (map[i][j + 1] == '\0'
			|| map[i - 1][j] == '\0' || map[i + 1][j] == '\0')
			return (ft_exit_error
				("Error : The map must be surrounded by walls (1)!"), 1);
		if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
			|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
			return (ft_exit_error
				("Error : The map must be surrounded by walls (1)!"), 1);
	}
	return (EXIT_SUCCESS);
}

int	map_info(t_parser **data, char *line, int fd)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	if (!check_wall(line))
		return (ft_exit_error
			("Error : The map must be surrounded by walls (1)!"), 1);
	while (line)
	{
		i++;
		if (!(*line) || !valid_map_content(line))
			return (ft_exit_error("Error : Invalid content"), 1);
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	close (fd);
	line = NULL;
	(*data)->height = i;
	return (i);
}

int	get_map_width(char **map, int height)
{
	size_t	width;
	int		i;

	i = 0;
	width = ft_strlen(map[i]);
	while (i < height)
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return ((int)width);
}

int	check_player(t_parser *data, int i, int j)
{
	int		count;

	i = -1;
	count = 0;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			check_borders(data, i, j);
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				count++;
				data->player = data->map[i][j];
				data->player_x = j;
				data->player_y = i;
			}
		}
	}
	if (count != 1)
		return (ft_exit_error("Error : It must be exactly 1 player!"), 1);
	if (!check_wall(data->map[i - 1]))
		return (ft_exit_error("Error : The map must be surrounded by 1s!"), 1);
	return (0);
}
