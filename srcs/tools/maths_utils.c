/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:47:11 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/02 11:35:56 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	deg_to_rad(double a)
{
	return ((a * M_PI) / 180.0);
}

double	fix_ang(double a)
{
	if (a >= 360)
		a -= 360;
	else if (a < 0)
		a += 360;
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
