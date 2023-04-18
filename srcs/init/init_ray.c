/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 04:15:43 by hiroaki           #+#    #+#             */
/*   Updated: 2023/04/18 17:57:43 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_pos	init_dir(t_fpos r_delta)
{
	t_pos	r_dir;

	if (r_delta.f_x < 0)
		r_dir.x = -1;
	else
		r_dir.x = 1;
	if (r_delta.f_y < 0)
		r_dir.y = -1;
	else
		r_dir.y = 1;
	return (r_dir);
}

t_fpos	init_side(t_fpos r_delta, t_pos p_pos)
{
	t_fpos	side;

	if (r_delta.f_x > 0)
		side.f_x = MAP_SCALE - (p_pos.x % MAP_SCALE);
	else
		side.f_x = p_pos.x % MAP_SCALE;
	if (r_delta.f_y > 0)
		side.f_y = MAP_SCALE - (p_pos.y % MAP_SCALE);
	else
		side.f_y = p_pos.y % MAP_SCALE;
	return (side);
}

t_fpos	init_delta(double angle)
{
	t_fpos	r_delta;

	r_delta.f_x = cos(deg_to_rad(angle));
	r_delta.f_y = -sin(deg_to_rad(angle));
	return (r_delta);
}

void	init_ray(double x, double w, t_ray *ray)
{
	ray->r_angle = ray->p_angle + FOV / 2.0 - x / w * FOV;
	if (fabs(ray->r_angle - ray->p_angle) < EPSILON)
		ray->r_angle = ray->p_angle + FOV / 2.0 - (x + 0.01) / w * FOV;
	ray->map.x = ray->p_pos.x / MAP_SCALE;
	ray->map.y = ray->p_pos.y / MAP_SCALE;
	ray->r_delta = init_delta(ray->r_angle);
	ray->r_dir = init_dir(ray->r_delta);
	ray->r_side = init_side(ray->r_delta, ray->p_pos);
}
