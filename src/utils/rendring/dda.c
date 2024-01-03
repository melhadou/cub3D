/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoelansa <yoelansa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:01:35 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 23:14:55 by yoelansa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*drawing_formula_x(t_mlx *mlx, double lineh, int i, int r)
{
	char	*dst;

	dst = NULL;
	if (mlx->rays[r].ray_angle >= M_PI && mlx->rays[r].ray_angle <= 2 * M_PI)
	{
		dst = mlx->north + (int)(i * (mlx->nh / lineh))
			% mlx->nh * mlx->line_lenght4
			+ (int)(mlx->rays[r].hit_x * mlx->nw
				/ TILE_SIZE) % mlx->nw * (mlx->bits_per_pixel4 / 8);
	}
	else if (mlx->rays[r].ray_angle >= 0 && mlx->rays[r].ray_angle <= M_PI)
	{
		dst = mlx->south + (int)(i * (mlx->sh / lineh))
			% mlx->sh * mlx->line_lenght1
			+ (int)(mlx->rays[r].hit_x * mlx->sw
				/ TILE_SIZE) % mlx->sw * (mlx->bits_per_pixel1 / 8);
	}
	return (dst);
}

char	*drawing_formula_y(t_mlx *m, double lineh, int i, int r)
{
	char	*dst;

	dst = NULL;
	if (((m->rays[r].ray_angle >= 0 && m->rays[r].ray_angle <= M_PI / 2)
			|| (m->rays[r].ray_angle >= (3 * M_PI)
				/ 2 && m->rays[r].ray_angle <= 2 * M_PI)))
	{
		dst = m->west + (int)(i * (m->wh / lineh))
			% m->wh * m->line_lenght2
			+ (int)(m->rays[r].hit_y * m->ww
				/ TILE_SIZE) % m->ww * (m->bits_per_pixel2 / 8);
	}
	else if (m->rays[r].ray_angle >= M_PI
		/ 2 && m->rays[r].ray_angle <= (3 * M_PI) / 2)
	{
		dst = m->east + (int)(i * (m->eh / lineh))
			% m->eh * m->line_lenght3
			+ (int)(m->rays[r].hit_y * m->ew
				/ TILE_SIZE) % m->ew * (m->bits_per_pixel3 / 8);
	}
	return (dst);
}

void	draw_textures(t_mlx *m, double lineh, int r, double y1)
{
	char	*dst;
	int		i;

	i = 0;
	if (lineh > WINDOW_HEIGHT)
		i = (lineh - WINDOW_HEIGHT) / 2;
	m->rays[r].ray_angle = angle_normalize(m->rays[r].ray_angle);
	while (i < lineh)
	{
		if (y1 >= WINDOW_HEIGHT)
			break ;
		if (m->rays[r].found_horz_wall_hit)
			dst = drawing_formula_x(m, lineh, i, r);
		else if (m->rays[r].found_vert_wall_hit)
			dst = drawing_formula_y(m, lineh, i, r);
		my_mlx_pixel_put(m->img, r, y1, *(unsigned int *)dst);
		y1++;
		i++;
	}
}

void	draw_floor(t_mlx *mlx, double wall_strip_height, double lineo, int r)
{
	int	i;

	i = wall_strip_height + lineo - 1;
	while (++i < WINDOW_HEIGHT)
		my_mlx_pixel_put(mlx->img, r, i, mlx->fl_color);
}
