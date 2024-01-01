/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:35:09 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/01 16:41:52 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit(1);
	else if (key == W_KEY)
	{
		mlx->player->walk_direction = 1;
		update_movment(mlx);
	}
	else if (key == S_KEY)
	{
		mlx->player->walk_direction = -1;
		update_movment(mlx);
	}
	else if (key == D_KEY)
		update_movment_sides(mlx, 1);
	else if (key == A_KEY)
		update_movment_sides(mlx, -1);
	else if (key == RIGHT_ARROW)
	{
		mlx->player->turn_direction = 1;
		mlx->player->rotation_angle += mlx->player->turn_direction * mlx->player->rotation_speed;
		mlx->player->rotation_angle = angle_normalize(mlx->player->rotation_angle);
	}
	else if (key == LEFT_ARROW)
	{
		mlx->player->turn_direction = -1;
		mlx->player->rotation_angle += mlx->player->turn_direction * mlx->player->rotation_speed;
		mlx->player->rotation_angle = angle_normalize(mlx->player->rotation_angle);
	}
	update_image(mlx);
	return (0);
}

void update_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &(mlx->img->bits_per_pixel),
                                    &mlx->img->line_lenght, &mlx->img->endian);
	cast_rays(mlx);
	render_3d_walls(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
}

int	key_relase(int key, t_mlx *mlx)
{
	if (key == W_KEY)
		mlx->player->walk_direction = 0;
	else if (key == S_KEY)
		mlx->player->walk_direction = 0;
	else if (key == D_KEY)
		mlx->player->walk_direction = 0;
	else if (key == A_KEY)
		mlx->player->walk_direction = 0;
	else if (key == RIGHT_ARROW)
		mlx->player->turn_direction = 0;
	else if (key == LEFT_ARROW)
		mlx->player->turn_direction = 0;
	return (0);
}

int	destroy_win(void)
{
	exit(1);
	return (0);
}

void update_movment(t_mlx *mlx)
{
	double y;
	double x;
	double move_step;

	move_step = mlx->player->walk_direction * mlx->player->walk_speed;
	x = mlx->player->x + cos(mlx->player->rotation_angle) * move_step;
	y = mlx->player->y + sin(mlx->player->rotation_angle) * move_step;
	if (!is_wall(mlx->player->x, y, mlx))
	{
		x = mlx->player->x + cos(mlx->player->rotation_angle) * move_step;
		mlx->player->y = y;
		if (!is_wall(x, y, mlx))
			mlx->player->x = x;
	}
	if (!is_wall(x, mlx->player->y, mlx))
	{
		y = mlx->player->y + sin(mlx->player->rotation_angle) * move_step;
		mlx->player->x = x;
		if (!is_wall(x, y, mlx))
			mlx->player->y = y;
	}
}

void update_movment_sides(t_mlx *mlx, int side)
{	
	double x ;
 	double y ;
	double move_step;

	move_step = mlx->player->walk_speed;
	x = mlx->player->x + cos(mlx->player->rotation_angle + M_PI_2 * side ) * move_step;
	y = mlx->player->y + sin(mlx->player->rotation_angle + M_PI_2 * side ) * move_step;

	if (!is_wall(mlx->player->x, y, mlx))
	{
		x = mlx->player->x + cos(mlx->player->rotation_angle + M_PI_2 * side ) * move_step;
		mlx->player->y = y;
		if (!is_wall(x, y, mlx))
			mlx->player->x = x;
	}
	if (!is_wall(x, mlx->player->y, mlx))
	{
		y = mlx->player->y + sin(mlx->player->rotation_angle + M_PI_2 * side ) * move_step;
		mlx->player->x = x;
		if (!is_wall(x, y, mlx))
			mlx->player->y = y;
	}
}
