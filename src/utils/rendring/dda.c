/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uns-35 <uns-35@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:01:35 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/31 16:34:56 by uns-35           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	dda(t_mlx mlx, t_player start, t_player end, double wall_height)
// {
// 	t_dda	dda;

// 	dda.dx = end.x - start.x;
// 	dda.dy = end.y - start.y;
// 	// dda.color = 0x00FF00;
// 	dda.color = end.color;
// 	dda.steps = fmaxf(fabs(dda.dx), fabs(dda.dy));
// 	dda.x_inc = dda.dx / dda.steps;
// 	dda.y_inc = dda.dy / dda.steps;
// 	dda.x = start.x;
// 	dda.y = start.y;
// 	while ((dda.steps--) >= 0)
// 	{
// 		my_mlx_pixel_put(mlx.img, \
// 			dda.x, \
// 			dda.y, \
// 			dda.color);
// 		dda.x += dda.x_inc;
// 		dda.y += dda.y_inc;
// 	}
// }

void	draw_textures(t_mlx *mlx, double lineh, int r, double y1)
{ 
	char	*dst;
	int		i;

	i = 0;
	if (lineh > WINDOW_HEIGHT)
		i = (lineh - WINDOW_HEIGHT) / 2;
	mlx->rays[r].ray_angle = angle_normalize(mlx->rays[r].ray_angle);
	while (i < lineh)
	{
		if (y1 >= WINDOW_HEIGHT)
			break ;
		if (mlx->rays[r].found_horz_wall_hit)
		{
			if (mlx->rays[r].ray_angle >= M_PI && mlx->rays[r].ray_angle <= 2 * M_PI){
				dst = mlx->north + (int)(i * (mlx->nh / lineh))
						% mlx->nh * mlx->line_lenght4
						+ (int)(mlx->rays[r].hit_x * mlx->nw / TILE_SIZE) % mlx->nw * (mlx->bits_per_pixel4 / 8);
			}
			else if (mlx->rays[r].ray_angle >= 0 && mlx->rays[r].ray_angle <= M_PI){
				dst = mlx->south + (int)(i * (mlx->sh / lineh))
						% mlx->sh * mlx->line_lenght1
						+ (int)(mlx->rays[r].hit_x * mlx->sw / TILE_SIZE) % mlx->sw * (mlx->bits_per_pixel1 / 8);
			}
		}
		else if (mlx->rays[r].found_vert_wall_hit) 
		{
			if (((mlx->rays[r].ray_angle >= 0 && mlx->rays[r].ray_angle <= M_PI / 2) || (mlx->rays[r].ray_angle >= (3*M_PI) / 2 && mlx->rays[r].ray_angle <= 2 * M_PI))){
				dst = mlx->west + (int)(i * (mlx->wh / lineh))
						% mlx->wh * mlx->line_lenght2
						+ (int)(mlx->rays[r].hit_y * mlx->ww / TILE_SIZE) % mlx->ww * (mlx->bits_per_pixel2 / 8);
			}
			else if (mlx->rays[r].ray_angle >= M_PI / 2 && mlx->rays[r].ray_angle <= (3*M_PI) / 2){
				dst = mlx->east + (int)(i * (mlx->eh / lineh))
						% mlx->eh * mlx->line_lenght3
						+ (int)(mlx->rays[r].hit_y * mlx->ew / TILE_SIZE) % mlx->ew * (mlx->bits_per_pixel3 / 8);
			}
		}
		my_mlx_pixel_put(mlx->img, r, y1, *(unsigned int *)dst);
		y1++;
		i++;
	}
}

void     draw_floor(t_mlx *mlx, double wall_strip_height, double lineo, int r)
{
	int i = wall_strip_height+lineo;
	while (i < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(mlx->img, r, i, mlx->fl_color);
		i++;
	}
}
void    draw_ceilling(t_mlx *mlx, double lineo, int r)
{
	int i = 0;
	while (i < lineo)
	{
		my_mlx_pixel_put(mlx->img, r, i, mlx->ceil_color);
		i++;
	}
}

int	rgb_to_hex(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}




