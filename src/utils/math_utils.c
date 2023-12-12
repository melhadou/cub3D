/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melhadou <melhadou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:42:09 by melhadou          #+#    #+#             */
/*   Updated: 2023/12/11 17:25:46 by melhadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double deg2rad(double deg)
{
	return (deg * (M_PI / 180));
}

double rad2deg(double rad)
{
	return (rad * (180 / M_PI));
}
