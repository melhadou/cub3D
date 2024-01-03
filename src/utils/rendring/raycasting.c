/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:56:37 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 00:55:42 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_ray	*horizontal_intersection(t_mlx *mlx, int i)
{
	t_cast	core;
	t_ray	*ray;

	mlx->rays[i].found_horz_wall_hit = 0;
	ray = malloc(sizeof(t_ray));
	core.yintercept = floor(mlx->player->y / (double)TILE_SIZE) * TILE_SIZE;
	if (mlx->rays[i].rayfacing_down)
		core.yintercept += TILE_SIZE;
	core.xintercept = mlx->player->x + \
		(core.yintercept - mlx->player->y) / tan(mlx->rays[i].ray_angle);
	core.ystep = TILE_SIZE;
	if (mlx->rays[i].rayfacing_up)
		core.ystep *= -1;
	core.xstep = TILE_SIZE / tan(mlx->rays[i].ray_angle);
	if (mlx->rays[i].rayfacing_left && core.xstep > 0)
		core.xstep *= -1;
	else if (mlx->rays[i].rayfacing_right && core.xstep < 0)
		core.xstep *= -1;
	core.x = core.xintercept;
	core.y = core.yintercept;
	core_horizontal(mlx, core, ray, i);
	return (ray);
}

void	core_horizontal(t_mlx *mlx, t_cast core, t_ray *ray, int i)
{
	t_player	tmp;

	if (mlx->rays[i].rayfacing_up)
		core.y--;
	while (1)
	{
		if (is_wall(core.x, core.y, mlx))
		{
			tmp.x = core.x;
			tmp.y = core.y;
			mlx->rays[i].found_horz_wall_hit = 1;
			break ;
		}
		core.x += core.xstep;
		core.y += core.ystep;
	}
	if (mlx->rays[i].rayfacing_up)
		tmp.y++;
	if (mlx->rays[i].found_horz_wall_hit)
		ray->distance = dis_bitween_2_pts(*mlx->player, tmp) \
			* cos(mlx->rays[i].ray_angle - mlx->player->rotation_angle);
	else
		ray->distance = MAX_NB;
	ray->hit_x = tmp.x;
	ray->hit_y = tmp.y;
}

t_ray	*vertical_intersection(t_mlx *mlx, int i)
{
	t_cast	core;
	t_ray	*ray;

	mlx->rays[i].found_vert_wall_hit = 0;
	ray = malloc(sizeof(t_ray));
	core.xintercept = floor(mlx->player->x / (double)TILE_SIZE) * TILE_SIZE;
	if (mlx->rays[i].rayfacing_right)
		core.xintercept += TILE_SIZE;
	core.yintercept = mlx->player->y + (core.xintercept - mlx->player->x) \
		* tan(mlx->rays[i].ray_angle);
	core.xstep = TILE_SIZE;
	if (mlx->rays[i].rayfacing_left)
		core.xstep *= -1;
	core.ystep = TILE_SIZE * tan(mlx->rays[i].ray_angle);
	if (mlx->rays[i].rayfacing_up && core.ystep > 0)
		core.ystep *= -1;
	if (mlx->rays[i].rayfacing_down && core.ystep < 0)
		core.ystep *= -1;
	core.x = core.xintercept;
	core.y = core.yintercept;
	core_vertical(mlx, core, ray, i);
	return (ray);
}

void	core_vertical(t_mlx *mlx, t_cast core, t_ray *ray, int i)
{
	t_player	tmp;

	if (mlx->rays[i].rayfacing_left)
		core.x--;
	while (1)
	{
		if (is_wall(core.x, core.y, mlx))
		{
			tmp.x = core.x;
			tmp.y = core.y;
			mlx->rays[i].found_vert_wall_hit = 1;
			break ;
		}
		core.x += core.xstep;
		core.y += core.ystep;
	}
	if (mlx->rays[i].rayfacing_left)
		tmp.x++;
	if (mlx->rays[i].found_vert_wall_hit)
		ray->distance = dis_bitween_2_pts(*mlx->player, tmp) \
			* cos(mlx->rays[i].ray_angle - mlx->player->rotation_angle);
	else
		ray->distance = MAX_NB;
	ray->hit_x = tmp.x;
	ray->hit_y = tmp.y;
}
