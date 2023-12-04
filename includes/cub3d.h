/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:42:49 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/04 15:22:28 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include "../libs/libft/libft.h"
#include "../libs/mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TILE_SIZE 64
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define SPEED 5

// check for linux or mac
#ifdef __linux__

enum {
	ESC = 65307,
	MLX_MASK = (1L<<1),
};

#elif __APPLE__
enum {
	ESC = 53
	MLX_MASK = 0,
};
#endif

/* ****************** DDA struct ****************** */
typedef struct t_dda
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
	int		color;
}	t_dda;

typedef struct t_point
{
	double	x;
	double	y;
	int		color;
}	t_point;

/* ****************** put pixel struct ****************** */
typedef struct t_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}	t_data;

/* ****************** Mlx struct ****************** */
typedef struct t_mlx
{
	void *mlx;
	void *win;
	int cube_size;
	t_data *img;
}				t_mlx;

/* ****************** Math Util_Functions ****************** */
double deg2rad(double deg);
double rad2deg(double rad);

void draw_cube(t_mlx *mlx, int x, int y, int color);
void draw_map(int map[10][10], t_mlx mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_player(t_point player, t_mlx *mlx);


/* ****************** Events Util_Functions ****************** */
int	key_hook(int key, void *mlx);
int	destroy_win(void);

/* ****************** DDA Util_Functions ****************** */
void	dda(t_mlx mlx, t_point start, t_point end);

#endif
