/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:08:33 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/11 17:25:16 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player *player)
{
  player->x = (float) WINDOW_WIDTH / 2;
  player->y = (float) WINDOW_HEIGHT / 2;
	player->turn_direction = 0; // -1 for left, +1 for right
	player->walk_direction = 0; // -1 for back, +1 for front
	player->rotation_angle = M_PI / 2;
	player->walk_speed = 5;
	player->color = 0xff0;
	player->rotation_speed = deg2rad(5);
	player->fov_angle = deg2rad(60);
}

int main(int argc, char **argv) {
  t_mlx mlx;

  t_player player;
	t_ray rays[NB_RAYS];

  char map[10][10] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
                      {'1', '0', '0', '1', '1', '1', '0', '0', '1', '1'},
                      {'1', '0', '1', '0', '0', '1', '0', '0', '0', '1'},
                      {'1', '0', '1', '0', '0', '0', '0', '1', '1', '1'},
                      {'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
                      {'1', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
                      {'1', '0', '0', '0', '0', '1', '1', '0', '0', '1'},
                      {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

  mlx.map = malloc(10 * 10 * sizeof(char));
	mlx.map[0] = map[0];
	mlx.map[1] = map[1];
	mlx.map[2] = map[2];
	mlx.map[3] = map[3];
	mlx.map[4] = map[4];
	mlx.map[5] = map[5];
	mlx.map[6] = map[6];
	mlx.map[7] = map[7];
	mlx.map[8] = map[8];
	mlx.map[9] = map[9];


  mlx.img = malloc(sizeof(t_data));
  if (!mlx.img)
    exit(1);
  mlx.mlx = mlx_init();
  mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
  mlx.img->img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx.img->addr = mlx_get_data_addr(mlx.img->img, &(mlx.img->bits_per_pixel),
                                    &mlx.img->line_lenght, &mlx.img->endian);
  mlx.cube_size = 64;
	init_player(&player);
  mlx.player = &player;
	mlx.rays = rays;

  draw_map(&mlx);
	cast_rays(&mlx);
	render_rays(&mlx);
  draw_player(&mlx);

	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 0, 0);
	mlx_hook(mlx.win, 2, MLX_MASK, &key_press, &mlx);
	mlx_hook(mlx.win, 3, MLX_MASK, &key_relase, &mlx);
  mlx_hook(mlx.win, 17, MLX_MASK, &destroy_win, &mlx);

  mlx_loop(mlx.mlx);
  return (EXIT_SUCCESS);
}
