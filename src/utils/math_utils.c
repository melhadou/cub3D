/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:42:09 by melhadou          #+#    #+#             */
/*   Updated: 2024/01/03 01:03:02 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg2rad(double deg)
{
	return (deg * (M_PI / 180));
}

double	rad2deg(double rad)
{
	return (rad * (180 / M_PI));
}

void	draw_ceilling(t_mlx *mlx, double lineo, int r)
{
	int	i;

	i = -1;
	while (++i < lineo)
		my_mlx_pixel_put(mlx->img, r, i, mlx->ceil_color);
}

int	rgb_to_hex(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
