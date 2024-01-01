/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:15:43 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/01 14:59:03 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t arr_len(char **arr)
{
  size_t len;

  len = 0;
  while (arr[len] != NULL)
    len++;
  return len;
}

int out_of_border(double x, double y, t_mlx *mlx)
{
  int x1 = floor(x / TILE_SIZE);
  int y1 = floor(y / TILE_SIZE);

  if (y1 >= arr_len(mlx->map) || x1 >= ft_strlen(mlx->map[y1]))
    return (1);
  return 0;
}

/* @: check if the player is in a wall or not.*/
int is_wall(double x, double y, t_mlx *mlx)
{
  if (out_of_border(x, y, mlx))
    return 1;
  int x1 = floor(x / (double)TILE_SIZE);
  int y1 = floor(y / (double)TILE_SIZE);
  if (mlx->map[y1][x1] == '1')
    return (1);
  return (0);
}

double angle_normalize(double angle) {
  if (angle < 0)
    angle += deg2rad(360);
  if (angle > deg2rad(360))
    angle -= deg2rad(360);
  return (angle);
}

void get_direction(t_mlx *mlx, int i, double ray_angle)
{
	mlx->rays[i].rayfacing_down = ray_angle > 0 && ray_angle < M_PI;
	mlx->rays[i].rayfacing_up = !mlx->rays[i].rayfacing_down;
	mlx->rays[i].rayfacing_right = ray_angle < 0.5 * M_PI 
		|| ray_angle > 1.5 * M_PI;
	mlx->rays[i].rayfacing_left = !mlx->rays[i].rayfacing_right;
}

void set_corr_values(t_mlx *mlx, int i)
{
  t_ray *horz_tmp;
  t_ray *verti_tmp;
  
	verti_tmp = vertical_intersection(mlx, i);
	horz_tmp = horizontal_intersection(mlx, i);
	if (verti_tmp->distance < horz_tmp->distance)
	{
		mlx->rays[i].distance = verti_tmp->distance;
		mlx->rays[i].hit_y = verti_tmp->hit_y;
		mlx->rays[i].hit_x = verti_tmp->hit_x;
		mlx->rays[i].found_vert_wall_hit = 1;
		mlx->rays[i].found_horz_wall_hit = 0;
	}
	else
	{
		mlx->rays[i].distance = horz_tmp->distance;
		mlx->rays[i].hit_y = horz_tmp->hit_y;
		mlx->rays[i].hit_x = horz_tmp->hit_x;
		mlx->rays[i].found_horz_wall_hit = 1;
		mlx->rays[i].found_vert_wall_hit = 0;
	}
	free(verti_tmp);
	free(horz_tmp);
}

void cast_rays(t_mlx *mlx)
{
  int i;
	double ray_angle;

  i = 0;
  ray_angle = mlx->player->rotation_angle - (mlx->player->fov_angle / 2);
  while (i < NB_RAYS) {
    mlx->rays[i].ray_angle = ray_angle;
		get_direction(mlx, i, ray_angle);
		set_corr_values(mlx, i);
    ray_angle += mlx->player->fov_angle / (double)NB_RAYS;
    ray_angle = angle_normalize(ray_angle);
    i++;
  }
}

double distanceBetweenPoints(t_player p1, t_player p2)
{
  return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

void core_3d_rendrer(t_mlx *mlx, int i, double wall_strip_height)
{
	int side;

	if (mlx->rays[i].found_horz_wall_hit)
	{
		if (mlx->rays[i].rayfacing_down)
			side = 2;
		else
			side = 1;
	}
	if (mlx->rays[i].found_vert_wall_hit)
	{
		if (mlx->rays[i].rayfacing_left)
			side = 4;
		else
			side = 3;
	}
	wall_strip_height = (TILE_SIZE * WINDOW_HEIGHT) / mlx->rays[i].distance;
	double var = wall_strip_height;
	if (var > WINDOW_HEIGHT)
		var = WINDOW_HEIGHT;
	double lineo = (WINDOW_HEIGHT / 2.0) - (var / 2.0);
	draw_textures(mlx, wall_strip_height, i, lineo);
	draw_floor(mlx, wall_strip_height, lineo, i);
	draw_ceilling(mlx, lineo, i);
}

void render_3d_walls(t_mlx *mlx)
{
  double ray_distance;
  double dist_project_plane;
  double wall_strip_height;
  int i;

  i = 0;
  while (i < NB_RAYS)
	{
    // ray_distance = mlx->rays[i].distance;
    // dist_project_plane =
    //     ((double)WINDOW_WIDTH / 2) / tan(mlx->player->fov_angle / 2);
    // wall_strip_height = ((double)TILE_SIZE / ray_distance)* dist_project_plane;
		core_3d_rendrer(mlx, i, wall_strip_height);
		i++;
	}
}
