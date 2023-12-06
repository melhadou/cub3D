/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:35:09 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/06 17:24:32 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int key, t_mlx *mlx)
{
	if (key == ESC)
		exit(1);
	else if (key == W_KEY)
	{
		mlx->player->y -= 5;
	}
	else if (key == S_KEY)
	{
		mlx->player->y += 5;
	}
	else if (key == D_KEY)
	{
		mlx->player->x += 5;
	}
	else if (key == A_KEY)
	{
		mlx->player->x -= 5;
	}
	else if (key == RIGHT_ARROW)
	{
		mlx->player->rotation_angle -= 0.1;
	}
	else if (key == LEFT_ARROW)
	{
		mlx->player->rotation_angle += 0.1;
	}
	draw_map(mlx);
	draw_player(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	return (0);
}

int	destroy_win(void)
{
	exit(1);
	return (0);
}
