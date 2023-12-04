/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:28:55 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/01 23:41:57 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	if (x <= 0 || x >= WINDOW_WIDTH)
		return ;
	if (y <= 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	// *(unsigned int *)dst = color;
}

void draw_cube(t_mlx *mlx, int x, int y, int color)
{
	int i;
	int j;

	x *= mlx->cube_size;
	y *= mlx->cube_size;
	
	i = x;
	while(i < x + mlx->cube_size){
		j = y;
		while(j < y + mlx->cube_size)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, i, j, color);
			j++;
		}
		i++;
	}
}

void draw_map(int map[10][10], t_mlx mlx){
	int i;
	int j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (map[i][j] == 1)
				draw_cube(&mlx, j, i, 0x00FF0000);
			else
				draw_cube(&mlx, j, i, 0x00FFFFFF);
			// draw vertical lines and horizontal lines
			// dda(mlx, (t_point){j * mlx.cube_size, i * mlx.cube_size}, (t_point){j * mlx.cube_size + mlx.cube_size, i * mlx.cube_size});
			j++;
		}
		i++;
	}
}

void	draw_player(t_point player, t_mlx *mlx)
{
	int x = player.x;
	int y = player.y;
	int i;
	int j;

	i = x;
	while(i < x + 3){
		j = y;
		while(j < y + 3)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, i, j, 0x0000FF);
			j++;
		}
		i++;
	}
}
