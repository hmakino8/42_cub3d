/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:47:11 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 10:37:38 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	deg_to_rad(int a)
{
	return ((a * M_PI) / 180.0);
}

int	fix_ang(int a)
{
	if (a >= 360)
		a -= 360;
	else if (a < 0)
		a += 360;
	return (a);
}

float	do_div(float num, float denum)
{
	if (denum == 0)
	{
		if (num > 0)
			return (FLT_MAX);
		else
			return (-FLT_MAX);
	}
	else
		return (num / denum);
}
