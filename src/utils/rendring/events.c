/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:35:09 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/23 18:55:43 by melhadou         ###   ########.fr       */
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
	{
		// should move to the right of the plyer looking
		update_movment_sides(mlx, 1);
	}
	else if (key == A_KEY)
	{
		// should move to the left of the plyer looking
		update_movment_sides(mlx, -1);
	}
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
	// need to check if the
	mlx_destroy_image(mlx->mlx, mlx->img->img);
  mlx->img->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx->img->addr = mlx_get_data_addr(mlx->img->img, &(mlx->img->bits_per_pixel),
                                    &mlx->img->line_lenght, &mlx->img->endian);
  // draw_map(mlx);
	cast_rays(mlx);
  // draw_player(mlx);
	render_3d_walls(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	return (0);
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
	double move_step = mlx->player->walk_direction * mlx->player->walk_speed;
	double x = mlx->player->x + cos(mlx->player->rotation_angle) * move_step;
	double y = mlx->player->y + sin(mlx->player->rotation_angle) * move_step;

	if (!is_wall(x, y, mlx))
	{
		mlx->player->x = x;
		mlx->player->y = y;
	}
}

void update_movment_sides(t_mlx *mlx, int side)
{
	double move_step = mlx->player->walk_speed;
	double x = mlx->player->x + cos(mlx->player->rotation_angle + M_PI_2 * side ) * move_step;
	double y = mlx->player->y + sin(mlx->player->rotation_angle + M_PI_2 * side ) * move_step;

	if (!is_wall(x, y, mlx))
	{
		mlx->player->x = x;
		mlx->player->y = y;
	}
}
