/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:08:33 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/26 20:45:26 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_printer(t_parser *data)
{
	int	i;

	i = 0;
	printf("South : '%s'\n", data->n);
	printf("South : '%s'\n", data->w);
	printf("South : '%s'\n", data->e);
	printf("South : '%s'\n\n", data->s);
	printf("Floor (");
	for (i = 0; i < 3; i++)
	{
		printf("%d", data->floor[i]);
		if (i < 2)
			printf(",");
	}
	printf(")\nCeil (");
	for (i = 0; i < 3; i++)
	{
		printf("%d", data->ceil[i]);
		if (i < 2)
			printf(",");
	}
	printf(")\n\nHeight : '%d'", data->height);
	printf("\nWidth : '%d'\n", data->width);
}

void init_player(t_player *player)
{
  // player->x = 300; 
	// player->y = 100;
	player->turn_direction = 0; // -1 for left, +1 for right
	player->walk_direction = 0; // -1 for back, +1 for front
	player->rotation_angle = M_PI / 2;
	player->walk_speed = 10;
	player->color = 0xff0;
	player->rotation_speed = deg2rad(5);
	player->fov_angle = deg2rad(60);
}

int main(int ac, char **av) {

  t_mlx mlx;
  t_player player;
	t_ray rays[NB_RAYS];
	int fd;
	t_parser *data;
	char *line;
	
	if (ac != 2)
		return (ft_exit_error("Error : Try two arguments.."), 1);
	data = malloc(sizeof(t_parser));
	if (!data)
		return (ft_exit_error("Error : malloc failed.."), 1);
	filename_check_open(av[1], &fd);
	data_initialize(&data);
	line = "";
	parser_brain(&data, &fd, line, av[1]);
  // char map[10][10] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
  //                     {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
  //                     {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
  //                     {'1', '0', '0', '1', '1', '1', '0', '0', '1', '1'},
  //                     {'1', '0', '1', '0', '0', '1', '0', '0', '0', '1'},
  //                     {'1', '0', '1', '0', '0', '0', '0', '1', '1', '1'},
  //                     {'1', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
  //                     {'1', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
  //                     {'1', '0', '0', '0', '0', '1', '1', '0', '0', '1'},
  //                     {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

 //  char map[10][10] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
 //                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
 //                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
 //                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
 //                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
 //                      {'1', '0', '0', '0', '1', '0', '0', '0', '0', '1'},
 //                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
 //                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
 //                      {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
 //                      {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

 //  mlx.map = malloc(11 * 10 * sizeof(char));
	// mlx.map[0] = map[0];
	// mlx.map[1] = map[1];
	// mlx.map[2] = map[2];
	// mlx.map[3] = map[3];
	// mlx.map[4] = map[4];
	// mlx.map[5] = map[5];
	// mlx.map[6] = map[6];
	// mlx.map[7] = map[7];
	// mlx.map[8] = map[8];
	// mlx.map[9] = map[9];
	// mlx.map[10] = NULL;

	// mlx.map_width = 10;
	// mlx.map_width = 10;
  mlx.img = malloc(sizeof(t_data));
  if (!mlx.img)
    exit(1);
  mlx.mlx = mlx_init();
  mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
  mlx.img->img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
  mlx.img->addr = mlx_get_data_addr(mlx.img->img, &(mlx.img->bits_per_pixel),
                                    &mlx.img->line_lenght, &mlx.img->endian);
	init_player(&player);
  mlx.cube_size = TILE_SIZE;
  mlx.player = &player;
	mlx.rays = rays;
	
	mlx.map = data->map;

	mlx.map_width = data->width;
	mlx.map_height = data->height;
	mlx.player->x = data->player_x * TILE_SIZE + (double)TILE_SIZE / 2;
	mlx.player->y = data->player_y * TILE_SIZE + (double)TILE_SIZE / 2;

  // draw_map(&mlx);
	cast_rays(&mlx);
  // draw_player(&mlx);
	render_3d_walls(&mlx);

	// ft_printer(data);
	
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 0, 0);
	mlx_hook(mlx.win, 2, MLX_MASK, &key_press, &mlx);
	mlx_hook(mlx.win, 3, MLX_MASK, &key_relase, &mlx);
  mlx_hook(mlx.win, 17, MLX_MASK, &destroy_win, &mlx);
  
	// ft_free(data->map);
	// free(data);
	mlx_loop(mlx.mlx);
  return (EXIT_SUCCESS);
}
