/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 04:15:10 by hiroaki           #+#    #+#             */
/*   Updated: 2023/04/21 16:40:40 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	do_raycasting(t_ray *ray, t_fpos *r_pos, t_fpos *r_side)
{
	double	r_tan;

	r_tan = tan(deg_to_rad(ray->r_angle));
	if (fabs(r_tan) < EPSILON)
		r_tan = EPSILON;
	if (fabs(r_tan) * r_side->f_x > r_side->f_y)
	{
		r_pos->f_x = (double)ray->p_pos.x + r_side->f_y / -r_tan * ray->r_dir.y;
		r_pos->f_y = (double)ray->p_pos.y + r_side->f_y * ray->r_dir.y;
		r_side->f_y += MAP_SCALE;
		ray->slide = Y_SLIDE;
	}
	else
	{
		r_pos->f_x = (double)ray->p_pos.x + r_side->f_x * ray->r_dir.x;
		r_pos->f_y = (double)ray->p_pos.y + r_side->f_x * -r_tan * ray->r_dir.x;
		r_side->f_x += MAP_SCALE;
		ray->slide = X_SLIDE;
	}
}
