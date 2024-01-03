/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:06:01 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 00:52:35 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	set_player_direction(t_mlx *mlx, t_parser *data)
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

t_parser	*init_parse(int ac, char **av)
{
	t_parser	*data;
	int			fd;
	char		*line;

	if (ac != 2)
		ft_exit_error("Error : Try two arguments..");
	data = malloc(sizeof(t_parser));
	if (!data)
		ft_exit_error("Error : malloc failed..");
	filename_check_open(av[1], &fd);
	data_initialize(&data);
	line = "";
	parser_brain(&data, &fd, line, av[1]);
	return (data);
}

void	init_mlx_img(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	mlx->img->img = mlx_new_image(mlx->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, \
		&(mlx->img->bits_per_pixel), &mlx->img->line_lenght, \
		&mlx->img->endian);
}

void	core_game(t_mlx *mlx, t_player *player, t_parser *data, t_ray *rays)
{
	init_player(player);
	mlx->mouse_x = 0;
	mlx->cube_size = TILE_SIZE;
	mlx->player = player;
	mlx->rays = rays;
	mlx->map = data->map;
	mlx->map_width = data->width;
	mlx->map_height = data->height;
	mlx->player->x = data->player_x * TILE_SIZE + (double)TILE_SIZE / 2;
	mlx->player->y = data->player_y * TILE_SIZE + (double)TILE_SIZE / 2;
	set_player_direction(mlx, data);
	get_textures(mlx, data);
	mlx->ceil_color = rgb_to_hex(data->ceil);
	mlx->fl_color = rgb_to_hex(data->floor);
	cast_rays(mlx);
	render_3d_walls(mlx);
}
