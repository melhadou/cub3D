/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:15:43 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/20 19:52:31 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* @: check if the player is in a wall or not.*/
int is_wall(double x, double y, t_mlx *mlx){ 
	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
		return (1);
	int x1 = floor(x / TILE_SIZE);
	int y1 = floor(y / TILE_SIZE);
	if (mlx->map[y1][x1] == '1')
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
	int i;
	t_ray *horz_tmp;
	t_ray *verti_tmp;

	double ray_angle = mlx->player->rotation_angle - (mlx->player->fov_angle / 2);
	i = 0;
	while(i < NB_RAYS)
	{
		mlx->rays[i].ray_angle = ray_angle;
		
		// checking direction of the ray
		mlx->rays[i].rayfacing_down = ray_angle > 0 && ray_angle < deg2rad(180);
		mlx->rays[i].rayfacing_up = !mlx->rays[i].rayfacing_down; // checking for the opposite
		mlx->rays[i].rayfacing_right = ray_angle < deg2rad(90) || ray_angle > deg2rad(270);
		mlx->rays[i].rayfacing_left = !mlx->rays[i].rayfacing_right;

		verti_tmp = vertical_intersection(mlx, i);
		horz_tmp = horizontal_intersection(mlx, i);
	
		// record x and y of ray
		mlx->rays[i].distance = verti_tmp->distance;
		// mlx->rays[i].hit_y = horz_tmp->hit_y;
		// mlx->rays[i].hit_x = horz_tmp->hit_x;
		if (horz_tmp->distance < verti_tmp->distance)
		{
			mlx->rays[i].distance = horz_tmp->distance;
			// mlx->rays[i].hit_y = horz_tmp->hit_y;
			// mlx->rays[i].hit_x = verti_tmp->hit_x;
		}
		// dda(*mlx, (t_player){mlx->player->x, mlx->player->y}, (t_player){mlx->rays[i].hit_x, mlx->rays[i].hit_y});
		free(verti_tmp);
		free(horz_tmp);
		ray_angle += mlx->player->fov_angle / NB_RAYS;
		ray_angle = angleNormalizeInDegree(ray_angle);
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
	t_player p1;
	t_player p2;
	p2.color = 0xe00fa0;
	while(i < NB_RAYS)
	{
		ray_distance = mlx->rays[i].distance;
		dist_project_plane = ((float)WINDOW_WIDTH / 2) / tan(mlx->player->fov_angle / 2);
		wall_strip_height = (TILE_SIZE / ray_distance) * dist_project_plane;
		// draw_rectangle((t_player){i * wall_strip_height,
		// 	(((float)WINDOW_WIDTH / 2) - (wall_strip_height / 2))},
		// 	(t_player){10, wall_strip_height}, mlx, 0x00ff00);
		//
		//

		/* ------------------ trying color sepration ------------------ */
		// if (mlx->rays[i].rayfacing_up)
		// {
		// 	p2.color = 0x00ff00;
		// }
		// else if (mlx->rays[i].rayfacing_down)
		// {
		// 	p2.color = 0xff00ff;
		// }
		// else if (mlx->rays[i].rayfacing_down)
		// {
		// 	p2.color = 0xe00fa0;
		// }
		// else if (mlx->rays[i].rayfacing_down)
		// {
		// 	p2.color = 0xa0a000;
		// }

		p1.x = i;
		p1.y = ((float)WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		
		p2.x = i;
		p2.y = ((float)WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		dda(*mlx, p1, p2);
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
