/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:57:34 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/29 17:59:58 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_pos	get_side(t_pos pos, t_fpos delta)
{
	if (delta.f_x > 0)
		pos.x = BPP - (pos.x % BPP);
	else
		pos.x = pos.x % BPP;
	if (delta.f_y > 0)
		pos.y = BPP - (pos.y % BPP);
	else
		pos.y = pos.y % BPP;
	if (pos.x == 0)
		pos.x = BPP;
	if (pos.y == 0)
		pos.y = BPP;
	return (pos);
}

void	update_ray_pos(t_ray *ray)
{
	ray->r_pos = ray->p_pos;
	if (ray->slide == X_SLIDE)
	{
		ray->r_pos.x += (ray->p_side.x + ray->slide_cnt.x * BPP) * ray->r_dir.x;
		ray->r_pos.y += ((double)(ray->p_side.x + ray->slide_cnt.x * BPP)
				* (ray->r_delta.f_y / fabs(ray->r_delta.f_x)));
		ray->slide_cnt.x++;
	}
	else if (ray->slide == Y_SLIDE)
	{
		ray->r_pos.x += ((double)(ray->p_side.y + ray->slide_cnt.y * BPP)
				* (ray->r_delta.f_x / fabs(ray->r_delta.f_y)));
		ray->r_pos.y += (ray->p_side.y + ray->slide_cnt.y * BPP) * ray->r_dir.y;
		ray->slide_cnt.y++;
	}
	else
	{
		ray->r_pos.x += (ray->p_side.x + ray->slide_cnt.x * BPP) * ray->r_dir.x;
		ray->r_pos.y += (ray->p_side.y + ray->slide_cnt.y * BPP) * ray->r_dir.y;
		ray->slide_cnt.y++;
		ray->slide_cnt.x++;
	}
	ray->r_side = get_side(ray->r_pos, ray->r_delta);
}

void	set_next_slide(t_ray *ray)
{
	t_fpos	side_div_delta;
	double	epsilon;

	epsilon = 0.00001;
	side_div_delta.f_x = do_div(ray->r_side.x, fabs(ray->r_delta.f_x));
	side_div_delta.f_y = do_div(ray->r_side.y, fabs(ray->r_delta.f_y));
	if (fabs(side_div_delta.f_x - side_div_delta.f_y) < epsilon)
		ray->slide = XY_SLIDE;
	else if (side_div_delta.f_x < side_div_delta.f_y)
		ray->slide = X_SLIDE;
	else
		ray->slide = Y_SLIDE;
}
