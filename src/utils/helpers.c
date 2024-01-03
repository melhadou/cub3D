/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:15:43 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 01:02:45 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	arr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}

int	out_of_border(double x, double y, t_mlx *mlx)
{
	int	x1;
	int	y1;

	x1 = floor(x / TILE_SIZE);
	y1 = floor(y / TILE_SIZE);
	if (y1 >= arr_len(mlx->map) || x1 >= ft_strlen(mlx->map[y1]))
		return (1);
	return (0);
}

/* @: check if the player is in a wall or not.*/
int	is_wall(double x, double y, t_mlx *mlx)
{
	int	x1;
	int	y1;

	if (out_of_border(x, y, mlx))
		return (1);
	x1 = floor(x / (double)TILE_SIZE);
	y1 = floor(y / (double)TILE_SIZE);
	if (mlx->map[y1][x1] == '1')
		return (1);
	return (0);
}

double	angle_normalize(double angle)
{
	if (angle < 0)
		angle += deg2rad(360);
	if (angle > deg2rad(360))
		angle -= deg2rad(360);
	return (angle);
}

void	get_direction(t_mlx *mlx, int i, double ray_angle)
{
	mlx->rays[i].rayfacing_down = ray_angle > 0 && ray_angle < M_PI;
	mlx->rays[i].rayfacing_up = !mlx->rays[i].rayfacing_down;
	mlx->rays[i].rayfacing_right = ray_angle < 0.5 * M_PI \
		|| ray_angle > 1.5 * M_PI;
	mlx->rays[i].rayfacing_left = !mlx->rays[i].rayfacing_right;
}
