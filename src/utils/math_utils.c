/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:42:09 by melhadou          #+#    #+#             */
/*   Updated: 2023/11/27 00:30:16 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

double deg2rad(double deg) { return (deg * (M_PI / 180)); }
double rad2deg(double rad) { return (rad * (180 / M_PI)); }
