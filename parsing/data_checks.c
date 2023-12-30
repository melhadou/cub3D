/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:15:59 by yoelansa          #+#    #+#             */
/*   Updated: 2023/12/27 19:27:45 by uns-35           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	data_initialize(t_parser **data)
{
	(*data)->floor[0] = -1;
	(*data)->ceil[0] = -1;
	(*data)->s = NULL;
	(*data)->e = NULL;
	(*data)->w = NULL;
	(*data)->n = NULL;
	(*data)->width = 0;
	(*data)->height = 0;
	(*data)->map = NULL;
}

int	filename_check_open(char *name, int *fd)
{
	*fd = 0;
	if (!name[0] || name[0] == '.')
		return (ft_exit_error
			("Error: Try a valid name for your mapfile!"), -1);
	if (!ft_strrchr(name, '.'))
		return (ft_exit_error
			("Error: The map name must contain .cub extention!"), -1);
	else if (ft_strncmp(ft_strrchr(name, '.'), ".cub", 4))
		return (ft_exit_error("Error: Wrong extention. Try .cub"), -1);
	*fd = open(name, O_RDONLY);
	if (*fd < 0)
		return (ft_exit_error("Error : Try a valid file"), -1);
	return (0);
}

char	*pars_direction_name(char *line)
{
	char	*path;
	int		i;
	char	*str;

	i = 0;
	str = ft_strtrim(line, " \t\n");
	path = ft_strtrim(ft_strchr(str, ' '), " \t\n");
	if (!path)
		ft_exit_error("Error : Empty path!");
	free(str);
	while (path[i])
	{
		if (path[i] == ' ' || path[i] == '\t')
			ft_exit_error("Error : Path must not contain spaces");
		i++;
	}
	if (ft_strncmp(ft_strrchr(path, '.'), ".xpm", 5))
		ft_exit_error("Error : Path must have .xpm extention!");
	return (path);
}

int	data_ready(t_parser *data)
{
	if (!data)
		return (0);
	if (!data->n || !data->w || !data->s || !data->e)
		return (0);
	else if (*data->n && *data->s && *data->w && *data->e
		&& data->floor[0] != -1 && data->ceil[0] != -1)
		return (1);
	return (0);
}

int	valid_map_content(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'N' && str[i] != 'E'
			&& str[i] != 'W' && str[i] != ' ' && str[i] != 'S')
			return (0);
		i++;
	}
	return (1);
}
