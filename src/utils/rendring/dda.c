/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:01:35 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/01 12:12:42 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_mlx mlx, t_point start, t_point end)
{
	t_dda	dda;

	dda.dx = end.x - start.x;
	dda.dy = end.y - start.y;
	dda.color = 0x00FF0000; // black
	dda.steps = fmaxf(fabsf(dda.dx), fabsf(dda.dy));
	dda.x_inc = dda.dx / dda.steps;
	dda.y_inc = dda.dy / dda.steps;
	dda.x = start.x;
	dda.y = start.y;
	while ((int)(dda.steps--) >= 0)
	{
		my_mlx_pixel_put(mlx.img, \
			dda.x + (int)(WINDOW_WIDTH / 2), \
			dda.y + (int)(WINDOW_HEIGHT / 2), \
			dda.color);
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
	}
}
