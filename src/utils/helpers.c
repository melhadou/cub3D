/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:15:43 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/12 11:53:07 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int is_wall(double x, double y, t_mlx *mlx){
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (1);
	double x1 = floor(x / TILE_SIZE);
	double y1 = floor(y / TILE_SIZE);
	if (mlx->map[(int)y1][(int)x1] == '1')
		return (1);
	return (0);
}



double angleNormalizeInDegree(double angle)
{
	if (angle < 0)
		angle += deg2rad(360);
	if (angle > deg2rad(360))
		angle -= deg2rad(360);
	return (angle);
}

void cast_rays(t_mlx *mlx)
{
	int column_id;
	int i;

	double ray_angle = mlx->player->rotation_angle - (mlx->player->fov_angle / 2);
	i = 0;
	while(i < NB_RAYS)
	{
		mlx->rays[i].ray_angle = ray_angle;
		ray_angle += mlx->player->fov_angle / NB_RAYS;
		ray_angle = angleNormalizeInDegree(ray_angle);
		i++;
	}
}

void render_rays(t_mlx *mlx)
{
	int i;
	t_ray *rays = mlx->rays;
	t_player pt2;

	pt2.color = 0x00ff;
	i = 0;
	while(i < NB_RAYS)
	{
		pt2.x = mlx->player->x + cos(rays[i].ray_angle);
		pt2.y = mlx->player->y + sin(rays[i].ray_angle);
		while(!is_wall(pt2.x, pt2.y, mlx))
		{
			pt2.x += cos(rays[i].ray_angle) * 5;
			pt2.y += sin(rays[i].ray_angle) * 5;
		}
		pt2.x -= cos(rays[i].ray_angle) * 5;
		pt2.y -= sin(rays[i].ray_angle) * 5;
		while(!is_wall(pt2.x, pt2.y, mlx))
		{
			pt2.x += cos(rays[i].ray_angle);
			pt2.y += sin(rays[i].ray_angle);
			distanceBetweenPoints(*mlx->player, pt2);
		}
		dda(*mlx, *mlx->player, pt2);
		i++;
	}
}

double distanceBetweenPoints(t_player p1, t_player p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}
