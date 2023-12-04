/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:08:33 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/04 15:23:26 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

t_mlx mlx;
t_point player;

int render_next_frame(void *ptr) {
	draw_player(player, &mlx);
	return 0;
}

int main(int argc, char **argv)
{
	
	player.x = 100;
	player.y = 100;

	int map[10][10] ={
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,1,0,0,1,1},
		{1,0,1,0,0,1,0,0,0,1},
		{1,0,1,0,1,1,0,1,1,1},
		{1,0,1,0,1,0,0,0,0,1},
		{1,0,0,0,1,1,1,0,0,1},
		{1,0,0,0,0,1,1,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	mlx.img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);

	mlx.cube_size = 64;

	draw_map(map, mlx);
	draw_player(player, &mlx);

	mlx_hook(mlx.win, 3, MLX_MASK, &key_hook, &mlx);
	mlx_hook(mlx.win, 17, MLX_MASK, &destroy_win, &mlx);

	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS); 
}
