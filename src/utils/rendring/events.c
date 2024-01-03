/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:35:09 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 00:17:55 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit(1);
	movments_keys(mlx, key);
	arrow_keys(mlx, key);
	update_image(mlx);
	return (0);
}

void	movments_keys(t_mlx *mlx, int key)
{
	if (key == W_KEY)
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
}

void	arrow_keys(t_mlx *mlx, int key)
{
	if (key == RIGHT_ARROW)
	{
		mlx->player->turn_direction = 1;
		mlx->player->rotation_angle += mlx->player->turn_direction
			* mlx->player->rotation_speed;
		mlx->player->rotation_angle = \
				angle_normalize(mlx->player->rotation_angle);
	}
	else if (key == LEFT_ARROW)
	{
		mlx->player->turn_direction = -1;
		mlx->player->rotation_angle += mlx->player->turn_direction
			* mlx->player->rotation_speed;
		mlx->player->rotation_angle = \
			angle_normalize(mlx->player->rotation_angle);
	}
}

void	update_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, \
			&(mlx->img->bits_per_pixel), \
			&mlx->img->line_lenght, \
			&mlx->img->endian);
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
