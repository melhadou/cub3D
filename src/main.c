/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:08:33 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/02 23:31:11 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->rotation_angle = M_PI / 2;
	player->walk_speed = 10;
	player->color = 0xff0;
	player->rotation_speed = deg2rad(5);
	player->fov_angle = deg2rad(60);
}

int	main(int ac, char **av)
{
	t_player	player;
	t_parser	*data;
	t_mlx		mlx;
	t_ray		rays[NB_RAYS];

	data = init_parse(ac, av);
	mlx.img = malloc(sizeof(t_data));
	if (!mlx.img)
		exit(1);
	init_mlx_img(&mlx);
	core_game(&mlx, &player, data, rays);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img->img, 0, 0);
	mlx_hook(mlx.win, 6, 64, &mouse_move, &mlx);
	mlx_hook(mlx.win, 2, MLX_MASK, &key_press, &mlx);
	mlx_hook(mlx.win, 3, MLX_MOUSE, &key_relase, &mlx);
	mlx_hook(mlx.win, 17, MLX_MASK, &destroy_win, &mlx);
	mlx_loop(mlx.mlx);
	return (EXIT_SUCCESS);
}
