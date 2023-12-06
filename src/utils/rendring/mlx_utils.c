/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:28:55 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/06 17:22:49 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	if (x <= 0 || x >= WINDOW_WIDTH)
		return ;
	if (y <= 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_cube(t_mlx *mlx, int x, int y, int color)
{
	int i;
	int j;

	x *= mlx->cube_size;
	y *= mlx->cube_size;
	
	i = y;
	while(i < y + mlx->cube_size){
		j = x;
		while(j < x + mlx->cube_size)
		{
			my_mlx_pixel_put(mlx->img, j, i, color);
			j++;
		}
		i++;
	}
}

void draw_map(t_mlx *mlx)
{
	int y;
	int x;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			if (mlx->map[y][x] == '1')
				draw_cube(mlx, x, y, 0xFF0000);
			else
				draw_cube(mlx, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_player(t_mlx *mlx)
{
	int x = mlx->player->x;
	int y = mlx->player->y;
	int i;
	int j;

	i = x;
	while(i < x + 3){
		j = y;
		while(j < y + 3)
		{
			// mlx_pixel_put(mlx->mlx, mlx->win, i, j, 0x0000FF);
			dda(*mlx, (t_player){i,j}, (t_player){i + (20 * cos(mlx->player->rotation_angle)), j + (20 * sin(mlx->player->rotation_angle))});
			my_mlx_pixel_put(mlx->img, i, j, 0x0000FF);
			j++;
		}
		i++;
	}
	// draw a line in the direction of the player
}
