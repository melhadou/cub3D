/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:42:49 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/26 17:46:15 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include "parser.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TILE_SIZE 32
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define NB_RAYS WINDOW_WIDTH
// #define NB_RAYS 1
#define MAX_NB 100000000

#define SPEED 5

// check for linux or mac
#ifdef __linux__
#include "../libs/mlx/mlx.h"

enum {
	ESC = 65307,
	MLX_MASK = (1L<<0),
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363,
	W_KEY = 119,
	S_KEY = 115,
	A_KEY = 97,
	D_KEY = 100,
	RIGHT_ARROW = 65363,
	LEFT_ARROW = 65361,
};

#elif __APPLE__
#include "mlx.h"
enum {
	ESC = 53
	MLX_MASK = 0,
 	LEFT_KEY = 123,
 	RIGHT_KEY = 124,
	W_KEY = 119,
	S_KEY = 115,
	A_KEY = 97,
	D_KEY = 100,
};
#endif

typedef struct t_ray
{
	double hit_x;
	double hit_y;
	double ray_angle;
	double distance;
	double column_id;
	double color;
	int rayfacing_up;
	int rayfacing_down;
	int rayfacing_left;
	int rayfacing_right;
	int	found_horz_wall_hit;
	int	found_vert_wall_hit;
}	t_ray;

/* ****************** DDA struct ****************** */
typedef struct t_dda
{
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;
	double		color;
}	t_dda;

typedef struct t_player
{
	double	x;
	double	y;
	double	radius;
	double	turn_direction;
	double	walk_direction;
	double	rotation_angle;
	double	rotation_speed;
	double	walk_speed;
	double	fov_angle;
	double	color;
}	t_player;

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
	t_player *player;
	char **map;
	int map_width;
	int map_height;
	int cube_size;
	t_ray *rays;
	t_data *img;
}				t_mlx;

/* ****************** Math Util_Functions ****************** */
double deg2rad(double deg);
double rad2deg(double rad);

void draw_cube(t_mlx *mlx, int x, int y, int color);
void draw_map(t_mlx *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_player(t_mlx *mlx);

/* ****************** Events Util_Functions ****************** */
int	key_press(int key, t_mlx *mlx);
int	key_relase(int key, t_mlx *mlx);
int	destroy_win(void);
void update_movment(t_mlx *mlx);
void update_movment_sides(t_mlx *mlx, int side);

/* ****************** DDA Util_Functions ****************** */
void	dda(t_mlx mlx, t_player start, t_player end);

/* ****************** Helpers Util_Functions ****************** */
double angle_normalize(double angle);
int is_wall(double x, double y, t_mlx *mlx);
void cast_rays(t_mlx *mlx);
double distanceBetweenPoints(t_player p1, t_player p2);
void draw_rectangle(t_player p1, t_player p2, t_mlx *mlx, int color);
void render_3d_walls(t_mlx *mlx);
void clear_mlx_img(t_mlx *mlx);

/* ****************** Ray Casting Functions ****************** */
t_ray *vertical_intersection(t_mlx *mlx, int i);
t_ray *horizontal_intersection(t_mlx *mlx, int i);

#endif
