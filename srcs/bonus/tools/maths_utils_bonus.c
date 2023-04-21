/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:47:11 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 16:40:53 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

double	deg_to_rad(double a)
{
	return ((a * M_PI) / 180.0);
}

double	fix_ang(double a)
{
	if (a >= 360.0)
		a -= 360.0;
	else if (a < 0.0)
		a += 360.0;
	return (a);
}

double	do_div(double num, double denum)
{
	if (denum == 0)
	{
		if (num > 0)
			return (DBL_MAX);
		else
			return (-DBL_MAX);
	}
	else
		return (num / denum);
}
