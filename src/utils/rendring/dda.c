/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:01:35 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/11 17:15:53 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_mlx mlx, t_player start, t_player end)
{
	t_dda	dda;

	dda.dx = end.x - start.x;
	dda.dy = end.y - start.y;
	dda.color = end.color;
	dda.steps = fmaxf(fabsf(dda.dx), fabsf(dda.dy));
	dda.x_inc = dda.dx / dda.steps;
	dda.y_inc = dda.dy / dda.steps;
	dda.x = start.x;
	dda.y = start.y;
	while ((int)(dda.steps--) >= 0)
	{
		my_mlx_pixel_put(mlx.img, \
			dda.x, \
			dda.y, \
			dda.color);
		dda.x += dda.x_inc;
		dda.y += dda.y_inc;
	}
}
