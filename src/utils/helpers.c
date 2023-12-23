/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 18:15:43 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/23 18:55:13 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	arr_len(char **arr)
{
	size_t len;

	len = 0;
	while(arr[len] != NULL)
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
int is_wall(double x, double y, t_mlx *mlx){ 
	// if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
	// 	return (1);
	if (out_of_border(x, y, mlx))
		return 1;
	int x1 = floor(x / TILE_SIZE);
	int y1 = floor(y / TILE_SIZE);
	if (mlx->map[y1][x1] == '1')
			return (1);
	return (0);
}

double angle_normalize(double angle)
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
		mlx->rays[i].rayfacing_down = ray_angle > 0 && ray_angle < M_PI;
		mlx->rays[i].rayfacing_up = !mlx->rays[i].rayfacing_down; // checking for the opposite
		//
		mlx->rays[i].rayfacing_right = ray_angle < 0.5  * M_PI || ray_angle > 1.5  * M_PI;
		mlx->rays[i].rayfacing_left = !mlx->rays[i].rayfacing_right;

		// printf("--------------------------------\n");
		// printf("up => %d\n", mlx->rays[i].rayfacing_up);
		// printf("down => %d\n", mlx->rays[i].rayfacing_down);
		// printf("right => %d\n", mlx->rays[i].rayfacing_right );
		// printf("left => %d\n", mlx->rays[i].rayfacing_left);

		verti_tmp = vertical_intersection(mlx, i);
		horz_tmp = horizontal_intersection(mlx, i);
	
		// record x and y of ray
		mlx->rays[i].distance = horz_tmp->distance;
		mlx->rays[i].hit_y = horz_tmp->hit_y;
		mlx->rays[i].hit_x = horz_tmp->hit_x; // deault MAX_NB
		mlx->rays[i].found_horz_wall_hit = 1;
		mlx->rays[i].found_vert_wall_hit = 0;

		if (verti_tmp->distance < horz_tmp->distance)
		{
			mlx->rays[i].distance = verti_tmp->distance;
			mlx->rays[i].hit_y = verti_tmp->hit_y;
			mlx->rays[i].hit_x = verti_tmp->hit_x;
			mlx->rays[i].found_vert_wall_hit = 1;
			mlx->rays[i].found_horz_wall_hit = 0;
		}

		free(verti_tmp);
		free(horz_tmp);
		ray_angle += mlx->player->fov_angle / NB_RAYS;
		ray_angle = angle_normalize(ray_angle);
		dda(*mlx, (t_player){mlx->player->x, mlx->player->y}, (t_player){mlx->rays[i].hit_x, mlx->rays[i].hit_y});
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
	while(i < NB_RAYS)
	{
		ray_distance = mlx->rays[i].distance;
		dist_project_plane = ((double)WINDOW_WIDTH / 2) / tan(mlx->player->fov_angle / 2);
		wall_strip_height = (TILE_SIZE / ray_distance) * dist_project_plane;
		//
		//

		/* ------------------ trying color sepration ------------------ */

		if (mlx->rays[i].found_horz_wall_hit) {
			if (mlx->rays[i].rayfacing_down) {
				p2.color = 0x00ff00;
			}
			else {
				p2.color = 0xff00ff;
			}
		}

		else if (mlx->rays[i].found_vert_wall_hit) {
			if (mlx->rays[i].rayfacing_left) {
				p2.color = 0xe00fa0;
			}
			else {
				p2.color = 0xa0a000;
			}
		}
		// check or up and down, and should face horz
		// check or right and left, and should face  vert


		/* ------------------ trying color sepration ------------------ */
		// 
		// if (mlx->rays[i].rayfacing_up && mlx->rays[i].found_horz_wall_hit) {
		// }
		// else if (mlx->rays[i].rayfacing_down&& mlx->rays[i].found_vert_wall_hit) {
		// }
		// else if (mlx->rays[i].rayfacing_left && mlx->rays[i].found_horz_wall_hit) {
		// }
		// else if (mlx->rays[i].rayfacing_right && mlx->rays[i].found_vert_wall_hit) {
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
