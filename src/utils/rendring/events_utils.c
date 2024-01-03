/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:09:16 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 00:37:25 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_movment(t_mlx *mlx)
{
	double	y;
	double	x;
	double	move_step;

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
	else if (!is_wall(x, mlx->player->y, mlx))
	{
		y = mlx->player->y + sin(mlx->player->rotation_angle) * move_step;
		mlx->player->x = x;
		if (!is_wall(x, y, mlx))
			mlx->player->y = y;
	}
}

void	update_movment_sides(t_mlx *mlx, int side)
{
	double	x;
	double	y;
	double	move_step;

	move_step = mlx->player->walk_speed;
	x = mlx->player->x + \
		cos(mlx->player->rotation_angle + M_PI_2 * side) * move_step;
	y = mlx->player->y + \
		sin(mlx->player->rotation_angle + M_PI_2 * side) * move_step;
	if (!is_wall(mlx->player->x, y, mlx))
	{
		x = mlx->player->x + \
			cos(mlx->player->rotation_angle + M_PI_2 * side) * move_step;
		mlx->player->y = y;
		if (!is_wall(x, y, mlx))
			mlx->player->x = x;
	}
	else if (!is_wall(x, mlx->player->y, mlx))
	{
		y = mlx->player->y + \
			sin(mlx->player->rotation_angle + M_PI_2 * side) * move_step;
		mlx->player->x = x;
		if (!is_wall(x, y, mlx))
			mlx->player->y = y;
	}
}

int	mouse_move(int x, int y, t_mlx *mlx)
{
	if (x < mlx->mouse_x)
		arrow_keys(mlx, LEFT_ARROW);
	else if (x > mlx->mouse_x)
		arrow_keys(mlx, RIGHT_ARROW);
	update_image(mlx);
	mlx->mouse_x = x;
	return (0);
}

int	destroy_win(void)
{
	exit(1);
	return (0);
}
