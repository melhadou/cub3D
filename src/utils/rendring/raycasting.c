/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:56:37 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/20 15:34:27 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void horizontal_intersection(double ray_angle)
{
	double ystep;
	double xstep;

	ystep = TILE_SIZE;
	xstep = tan(ray_angle) / TILE_SIZE;
}

void vertical_intersection(double ray_angle)
{
	double xstep;
	double ystep;

	xstep = TILE_SIZE;
	ystep = tan(ray_angle) * TILE_SIZE;
}

void cast_ray_v2(t_mlx *mlx, int i)
{
	int j;
	double xstep;
	double ystep;
	double xintercept;
	double yintercept;
	double xtocheck;
	double ytocheck;
	t_player tmp;

	// find y cord of the closest horizontal grid intersection
	yintercept = floor(mlx->player->y / (double)TILE_SIZE) * TILE_SIZE;
	if (mlx->rays[i].rayfacing_down)
		yintercept += TILE_SIZE;
	// find x cond of the closest horizontal grid intersection
	xintercept = mlx->player->x + (yintercept - mlx->player->y) / tan(mlx->rays[i].ray_angle);
	// calcluate the increment xstep and ystep
	ystep = TILE_SIZE;
	if (mlx->rays[i].rayfacing_up)
		ystep *= -1;
	xstep = TILE_SIZE / tan(mlx->rays[i].ray_angle);
	if (mlx->rays[i].rayfacing_left && xstep > 0)
		xstep *= -1;
	else if (mlx->rays[i].rayfacing_right && xstep < 0)
		xstep *= -1;

	// used to find the cell containing the wall hit
	xtocheck = xintercept;
	ytocheck = yintercept;
	if (mlx->rays[i].rayfacing_up)
		ytocheck--;
	// increment xstep and ystep until we find a wall
	while(xtocheck >= 0 && xtocheck <= WINDOW_WIDTH && ytocheck >= 0 && ytocheck <= WINDOW_HEIGHT)
	{
		if (is_wall(xtocheck, ytocheck, mlx))
		{
			// calculate the distance
			tmp.x = xtocheck;
			tmp.y = ytocheck;
			// mlx->rays[i].distance = distanceBetweenPoints(*mlx->player, tmp) * cos(mlx->rays[i].ray_angle - mlx->player->rotation_angle);
			tmp.color = 0x00ff;
			dda(*mlx, *mlx->player, tmp);
			break;
		}
		xtocheck += xstep;
		ytocheck += ystep;
		// printf("xtocheck: %f, ytocheck: %f\n", xtocheck, ytocheck);
	}
}
