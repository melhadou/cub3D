/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:15:43 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/12 18:31:35 by melhadou         ###   ########.fr       */
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
		}	
		rays[i].distance = distanceBetweenPoints(*mlx->player, pt2);
		// dda(*mlx, *mlx->player, pt2);
		i++;
	}
}

double distanceBetweenPoints(t_player p1, t_player p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

void draw_rectangle(t_player p1, t_player p2, t_mlx *mlx, int color)
{
	int i;
	int j;
	
	i = p1.y;

	while(i < p2.y)
	{

		j = p1.x;
		while(j < p2.x)
		{
			my_mlx_pixel_put(mlx->img, j, i, color);
			j++;
		}
		i++;
	}
}

void render_3d_walls(t_mlx *mlx)
{
	double ray_distance;
	double dist_project_plane;
	double wall_strip_height;

	int i;

	i = 0;
	while(i < NB_RAYS)
	{
		ray_distance = mlx->rays[i].distance;
		// printf("ray_distance = %f\n", ray_distance);
		dist_project_plane = ((float)WINDOW_WIDTH / 2) / tan(mlx->player->fov_angle / 2);
		wall_strip_height = (TILE_SIZE / ray_distance) * dist_project_plane;
		// draw_rectangle((t_player){i * wall_strip_height,
		// 	(((float)WINDOW_WIDTH / 2) - (wall_strip_height / 2))},
		// 	(t_player){10, wall_strip_height}, mlx, 0x00ff00);
		//
		//


		t_player p1;
		t_player p2;

		p1.x = i;
		p1.y = ((float)WINDOW_HEIGHT / 2) - (wall_strip_height / 2);

		p2.x = i;
		p2.y = ((float)WINDOW_HEIGHT / 2) + (wall_strip_height / 2);


		dda(*mlx, p1, p2);
		// draw_rectangle(p1, p2, mlx, 0x00ff00);

		i++;
	}
}

void clear_mlx_img(t_mlx *mlx)
{
	int i;
	int j;

	i = 0;
	while(i < WINDOW_WIDTH)
	{
		j = 0;
		while(j < WINDOW_HEIGHT)
		{
			my_mlx_pixel_put(mlx->img, i, j, 0x000000);
			j++;
		}
		i++;
	}
}
