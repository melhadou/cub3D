/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:42:49 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 22:40:46 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "parser.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define TILE_SIZE 32
# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720
# define NB_RAYS WINDOW_WIDTH
# define MAX_NB 100000000
# define SPEED 5

/*
enum
{
	ESC = 65307,
	MLX_MASK = (1L<<0),
	MLX_MOUSE = (1L<<1),
	LEFT_KEY = 65361,
	RIGHT_KEY = 65363,
	W_KEY = 119,
	S_KEY = 115,
	A_KEY = 97,
	D_KEY = 100,
	RIGHT_ARROW = 65363,
	LEFT_ARROW = 65361,
};
*/
enum {
	ESC = 53,
	MLX_MOUSE = 1,
	MLX_MASK = 0,
 	LEFT_KEY = 123,
 	RIGHT_KEY = 124,
	W_KEY = 13,
	S_KEY = 1,
	A_KEY = 0,
	D_KEY = 2,
 	LEFT_ARROW = 123,
 	RIGHT_ARROW = 124,
};

typedef struct t_cast
{
	double	xstep;
	double	ystep;
	double	xintercept;
	double	yintercept;
	double	x;
	double	y;

}	t_cast;

typedef struct t_ray
{
	double	hit_x;
	double	hit_y;
	double	ray_angle;
	double	distance;
	double	column_id;
	double	color;
	int		rayfacing_up;
	int		rayfacing_down;
	int		rayfacing_left;
	int		rayfacing_right;
	int		found_horz_wall_hit;
	int		found_vert_wall_hit;
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
	double	color;
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
	// #unes
	int		height;
	int		width;
	//==
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}	t_data;

/* ****************** Mlx struct ****************** */
typedef struct t_mlx
{
	t_player		*player;
	t_data			*img;
	t_ray			*rays;
	// declaration for textures
	//==
	int				fl_color;
	int				ceil_color;

	char			*south;
	int				bits_per_pixel1;
	int				line_lenght1;
	int				endian1;
	int				sh; //width
	int				sw; //height
	//
	char			*west;
	int				bits_per_pixel2;
	int				line_lenght2;
	int				endian2;
	int				wh;
	int				ww;

	char			*east;
	int				bits_per_pixel3;
	int				line_lenght3;
	int				endian3;
	int				eh;
	int				ew;

	char			*north;
	int				bits_per_pixel4;
	int				line_lenght4;
	int				endian4;
	int				nh;
	int				nw;
	// -			-----------
	void			*mlx;
	void			*win;
	char			**map;
	int				map_width;
	int				map_height;
	int				cube_size;
	int				mouse_x;
}	t_mlx;

/* ****************** Math Util_Functions ****************** */
t_parser	*init_parse(int ac, char **av);
double		deg2rad(double deg);
double		rad2deg(double rad);

void		draw_cube(t_mlx *mlx, int x, int y, int color);
void		draw_map(t_mlx *mlx);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		draw_player(t_mlx *mlx);

/* ****************** Events Util_Functions ****************** */
int			key_press(int key, t_mlx *mlx);
int			key_relase(int key, t_mlx *mlx);
int			destroy_win(void);
void		update_movment(t_mlx *mlx);
void		update_movment_sides(t_mlx *mlx, int side);

/* ****************** DDA Util_Functions ****************** */
// void	dda(t_mlx mlx, t_player start, t_player end);
// void	dda(t_mlx mlx, t_player start, t_player end, double wall_height);
void		draw_textures(t_mlx *mlx, double lineh, int r, double y1);
void		draw_floor(t_mlx *mlx, double wsh, double lineo, int r);
void		draw_ceilling(t_mlx *mlx, double lineo, int r);
int			rgb_to_hex(int rgb[3]);
char		*drawing_formula_x(t_mlx *mlx, double lineh, int i, int r);
char		*drawing_formula_y(t_mlx *mlx, double lineh, int i, int r);

/* ****************** Helpers Util_Functions ****************** */
double		angle_normalize(double angle);
int			is_wall(double x, double y, t_mlx *mlx);
void		cast_rays(t_mlx *mlx);
double		dis_bitween_2_pts(t_player p1, t_player p2);
void		render_3d_walls(t_mlx *mlx);
void		set_corr_values(t_mlx *mlx, int i);
void		get_direction(t_mlx *mlx, int i, double ray_angle);
void		core_3d_rendrer(t_mlx *mlx, int i, double wsh);

/* ****************** Ray Casting Functions ****************** */
t_ray		*vertical_intersection(t_mlx *mlx, int i);
t_ray		*horizontal_intersection(t_mlx *mlx, int i);
void		core_vertical(t_mlx *mlx, t_cast core, t_ray *ray, int i);
void		core_horizontal(t_mlx *mlx, t_cast core, t_ray *ray, int i);

void		update_image(t_mlx *mlx);
void		arrow_keys(t_mlx *mlx, int key);
void		movments_keys(t_mlx *mlx, int key);
int			mouse_move(int x, int y, t_mlx *mlx);

/* ****************** General Helper Functions ****************** */
void		set_player_direction(t_mlx *mlx, t_parser *data);
void		core_game(t_mlx *mlx, t_player *p, t_parser *data, t_ray *rays);
void		init_player(t_player *player);
void		init_mlx_img(t_mlx *mlx);

#endif
