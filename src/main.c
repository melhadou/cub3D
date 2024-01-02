/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:08:33 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/02 19:29:48 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_printer(t_parser *data)
{
	int	i;

	i = 0;
	printf("north : '%s'\n", data->n);
	printf("west : '%s'\n", data->w);
	printf("east : '%s'\n", data->e);
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
	player->turn_direction = 0; // -1 for left, +1 for right
	player->walk_direction = 0; // -1 for back, +1 for front
	player->rotation_angle = M_PI / 2;
	player->walk_speed = 10;
	player->color = 0xff0;
	player->rotation_speed = deg2rad(5);
	player->fov_angle = deg2rad(60);
}

void	get_textures(t_mlx *m, t_parser *p)
{
	void	*south;
	void	*west;
	void	*east;
	void	*north;

	south = mlx_xpm_file_to_image(m->mlx, p->s, &m->sw, &m->sh);
	west = mlx_xpm_file_to_image(m->mlx, p->w, &m->ww, &m->wh);
	east = mlx_xpm_file_to_image(m->mlx, p->e, &m->ew, &m->eh);
	north = mlx_xpm_file_to_image(m->mlx, p->n, &m->nw, &m->nh);
	if (!south || !west || !east || !north)
		ft_exit_error("Error: Wrong path!");
	m->south = mlx_get_data_addr(south, &m->bits_per_pixel1,
			&m->line_lenght1, &m->endian1);
	m->west = mlx_get_data_addr(west, &m->bits_per_pixel2,
			&m->line_lenght2, &m->endian2);
	m->east = mlx_get_data_addr(east, &m->bits_per_pixel3,
			&m->line_lenght3, &m->endian3);
	m->north = mlx_get_data_addr(north, &m->bits_per_pixel4,
			&m->line_lenght4, &m->endian4);
}

void set_player_direction(t_mlx *mlx, t_parser *data)
{
	if (data->player == 'S')
		mlx->player->rotation_angle = deg2rad(270);
	else if (data->player == 'W')
		mlx->player->rotation_angle = deg2rad(180);
	else if (data->player == 'E')
		mlx->player->rotation_angle = deg2rad(0);
	else if (data->player == 'N')
		mlx->player->rotation_angle = deg2rad(90);
}

t_parser *init_parse(int ac, char **av)
{
	int fd;
	char *line;
	t_parser *data;

	if (ac != 2)
		ft_exit_error("Error : Try two arguments..");
	data = malloc(sizeof(t_parser));
	if (!data)
		ft_exit_error("Error : malloc failed..");
	filename_check_open(av[1], &fd);
	data_initialize(&data);
	line = "";
	parser_brain(&data, &fd, line, av[1]);
	return (0);
}

int main(int ac, char **av) {

  t_mlx mlx;
  t_player player;
	t_ray rays[NB_RAYS];
	int fd;
	t_parser *data;
	char *line;
	
	// if (ac != 2)
	// 	return (ft_exit_error("Error : Try two arguments.."), 1);
	// data = malloc(sizeof(t_parser));
	// if (!data)
	// 	return (ft_exit_error("Error : malloc failed.."), 1);
	// filename_check_open(av[1], &fd);
	// data_initialize(&data);
	// line = "";
	// parser_brain(&data, &fd, line, av[1]);
	// mlx.img = malloc(sizeof(t_data));
	
	if (!mlx.img)
	  exit(1);
	
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	mlx.img->img = mlx_new_image(mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx.img->addr = mlx_get_data_addr(mlx.img->img, &(mlx.img->bits_per_pixel),
	                                  &mlx.img->line_lenght, &mlx.img->endian);
	init_player(&player);
	mlx.mouse_x = 0;
  mlx.cube_size = TILE_SIZE;
  mlx.player = &player;
	mlx.rays = rays;
	mlx.map = data->map;
	mlx.map_width = data->width;
	mlx.map_height = data->height;
	mlx.player->x = data->player_x * TILE_SIZE + (double)TILE_SIZE / 2;
	mlx.player->y = data->player_y * TILE_SIZE + (double)TILE_SIZE / 2;
	set_player_direction(&mlx, data);

	get_textures(&mlx, data);
	mlx.ceil_color = rgb_to_hex(data->ceil);
	mlx.fl_color = rgb_to_hex(data->floor);
	cast_rays(&mlx);
	render_3d_walls(&mlx);

	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 0, 0);
	mlx_hook(mlx.win, 6, 64, &mouse_move, &mlx);
	mlx_hook(mlx.win, 2, MLX_MASK, &key_press, &mlx);
	mlx_hook(mlx.win, 3, (1L<<1), &key_relase, &mlx);
	mlx_hook(mlx.win, 17, MLX_MASK, &destroy_win, &mlx);
  
	mlx_loop(mlx.mlx);
	// ft_free(data->map);
	// free(data);
  return (EXIT_SUCCESS);
}
