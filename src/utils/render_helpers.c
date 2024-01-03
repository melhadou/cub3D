/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:10:52 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 14:56:13 by uns-35           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_corr_values(t_mlx *mlx, int i)
{
	t_ray	*horz_tmp;
	t_ray	*verti_tmp;

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

void	cast_rays(t_mlx *mlx)
{
	double	ray_angle;
	int		i;

	i = 0;
	ray_angle = mlx->player->rotation_angle - (mlx->player->fov_angle / 2);
	while (i < NB_RAYS)
	{
		mlx->rays[i].ray_angle = ray_angle;
		get_direction(mlx, i, ray_angle);
		set_corr_values(mlx, i);
		ray_angle += mlx->player->fov_angle / (double)NB_RAYS;
		ray_angle = angle_normalize(ray_angle);
		i++;
	}
}

double	dis_bitween_2_pts(t_player p1, t_player p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

void	core_3d_rendrer(t_mlx *mlx, int i, double wall_strip_height)
{
	double	var;
	double	lineo;

	var = wall_strip_height;
	if (var > WINDOW_HEIGHT)
		var = WINDOW_HEIGHT;
	lineo = (WINDOW_HEIGHT / 2.0) - (var / 2.0);
	draw_textures(mlx, wall_strip_height, i, lineo);
	draw_floor(mlx, wall_strip_height, lineo, i);
	draw_ceilling(mlx, lineo, i);
}

void	render_3d_walls(t_mlx *mlx)
{
	double	wall_strip_height;
	int		i;

	i = 0;
	while (i < NB_RAYS)
	{
		wall_strip_height = (TILE_SIZE * WINDOW_HEIGHT) / mlx->rays[i].distance;
		core_3d_rendrer(mlx, i, wall_strip_height);
		i++;
	}
}
//////THIS COMMENT BELONG TO core_3d_render() FUNCTION "just in case"
	// int		side;

	// if (mlx->rays[i].found_horz_wall_hit)
	// {
	// 	if (mlx->rays[i].rayfacing_down)
	// 		side = 2;
	// 	else
	// 		side = 1;
	// }
	// if (mlx->rays[i].found_vert_wall_hit)
	// {
	// 	if (mlx->rays[i].rayfacing_left)
	// 		side = 4;
	// 	else
	// 		side = 3;
	// }
//---------------------
//and thiis to render_3d_walls()
	// double	ray_distance;
	// double	dist_project_plane;
/*
// ray_distance = mlx->rays[i].distance;
// dist_project_plane =
//     ((double)WINDOW_WIDTH / 2) / tan(mlx->player->fov_angle / 2);
// wall_strip_height = ((double)TILE_SIZE / ray_distance)* dist_project_plane;
*/
