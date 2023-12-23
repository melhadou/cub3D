/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:56:37 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/23 18:07:23 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray *horizontal_intersection(t_mlx *mlx, int i)
{
	double xstep;
	double ystep;
	double xintercept;
	double yintercept;
	double horiz_x;
	double horiz_y;
	t_player tmp;
	t_ray *ray;

	mlx->rays[i].found_horz_wall_hit = 0;
	ray = malloc(sizeof(t_ray));
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
	else
		ystep *= 1;

	xstep = TILE_SIZE / tan(mlx->rays[i].ray_angle);
	if (mlx->rays[i].rayfacing_left && xstep > 0)
		xstep *= -1;
	else if (mlx->rays[i].rayfacing_right && xstep < 0)
		xstep *= -1;
	else
		xstep *= 1;

	// used to find the cell containing the wall hit
	horiz_x = xintercept;
	horiz_y = yintercept;
	// increment xstep and ystep until we find a wall
	while(horiz_x >= 0 && horiz_x <= WINDOW_WIDTH && horiz_y >= 0 && horiz_y <= WINDOW_HEIGHT)
	{
		if (mlx->rays[i].rayfacing_up)
			horiz_y--;
		if (is_wall(horiz_x, horiz_y, mlx))
		{
			// calculate the distance
			tmp.x = horiz_x;
			tmp.y = horiz_y;
			mlx->rays[i].found_horz_wall_hit = 1;
			// tmp.color = 0x00ff;
			// dda(*mlx, (t_player){mlx->player->x, mlx->player->y}, (t_player){tmp.x, tmp.y});
			break;
		}
		horiz_x += xstep;
		horiz_y += ystep;
		// printf("xtocheck: %f, ytocheck: %f\n", xtocheck, ytocheck);
	}
	if (mlx->rays[i].found_horz_wall_hit)
		ray->distance = distanceBetweenPoints(*mlx->player, tmp) * cos(mlx->rays[i].ray_angle - mlx->player->rotation_angle);
	else
		ray->distance = MAX_NB;
	// record x and y
	ray->hit_x = tmp.x;
	ray->hit_y = tmp.y;

	return (ray);
}

t_ray *vertical_intersection(t_mlx *mlx, int i)
{
	double xstep;
	double ystep;
	double xintercept;
	double yintercept;
	double vert_x;
	double vert_y;
	t_player tmp;
	t_ray *ray;

	mlx->rays[i].found_vert_wall_hit = 0;
	ray = malloc(sizeof(t_ray));
	// find x-cord of the closest vertical grid intersection

	xintercept = floor(mlx->player->x / TILE_SIZE) * TILE_SIZE;
	if (mlx->rays[i].rayfacing_right)
		xintercept += TILE_SIZE;

	// find y-cond of the closest vertical grid intersection
	yintercept = mlx->player->y + (xintercept - mlx->player->x) * tan(mlx->rays[i].ray_angle);

	xstep = TILE_SIZE;
	if (mlx->rays[i].rayfacing_left)
		xstep *= -1;

	ystep = TILE_SIZE * tan(mlx->rays[i].ray_angle);
	if (mlx->rays[i].rayfacing_up && ystep > 0)
		ystep *= -1;
	if (mlx->rays[i].rayfacing_down && ystep < 0)
		ystep *= -1;

	// used to find the cell containing the wall hit
	vert_x = xintercept;
	vert_y = yintercept;
	// increment xstep and ystep until we find a wall
	if (mlx->rays[i].rayfacing_left)
		vert_x--;
	while(vert_x >= 0 && vert_x <= WINDOW_WIDTH && vert_y >= 0 && vert_y <= WINDOW_HEIGHT)
	{
		if (is_wall(vert_x, vert_y, mlx))
		{
			tmp.x = vert_x;
			tmp.y = vert_y;
			// calculate the distance
			// dda(*mlx, (t_player){mlx->player->x, mlx->player->y}, tmp);
			mlx->rays[i].found_vert_wall_hit = 1;
			break;
		}
		vert_x += xstep;
		vert_y += ystep;
		// printf("x: %f, y: %f\n", vert_x, vert_y);
	}
	if (mlx->rays[i].found_vert_wall_hit)
		ray->distance = distanceBetweenPoints(*mlx->player, tmp) * cos(mlx->rays[i].ray_angle - mlx->player->rotation_angle);
	else
		ray->distance = MAX_NB;
	// record x and y
	ray->hit_x = tmp.x;
	ray->hit_y = tmp.y;

	return (ray);
}
