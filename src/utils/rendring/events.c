/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:35:09 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/04 15:24:22 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int key, void *mlx)
{
	if (key == ESC)
		exit(1);
	return (0);
}

int	destroy_win(void)
{
	exit(1);
	return (0);
}
