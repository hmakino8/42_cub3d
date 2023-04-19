/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 04:15:10 by hiroaki           #+#    #+#             */
/*   Updated: 2023/04/19 11:32:58 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calculate_dist_to_wall(t_ray *ray)
{
	double	error;
	double	x_dist;

	error = cos(deg_to_rad(ray->r_angle - ray->p_angle));
	x_dist = ray->r_pos.f_x - (double)ray->p_pos.x;
	return (x_dist / cos(deg_to_rad(ray->r_angle)) * error);
}

void	set_wall_size(t_data *data, t_ray *ray)
{
	ray->perp_w_dist = calculate_dist_to_wall(ray);
	ray->line_height = (double)data->win_size.h
		/ ray->perp_w_dist * (double)MAP_SCALE;
	ray->w_start = lroundf(((double)data->win_size.h / 2.0)
			- ((double)ray->line_height / 2.0));
	ray->w_end = lroundf(((double)data->win_size.h / 2.0)
			+ ((double)ray->line_height / 2.0));
	ray->w_height = ray->w_end - ray->w_start;
	if (ray->slide == X_SLIDE)
		ray->wall_hit_x = (int)ray->r_pos.f_y % MAP_SCALE;
	else
		ray->wall_hit_x = (int)ray->r_pos.f_x % MAP_SCALE;
}

void	ray_collision_detection(t_data *data, t_ray *ray)
{
	while (data->map.array[ray->map.y][ray->map.x] != WALL)
	{
		do_raycasting(ray, &ray->r_pos, &ray->r_side);
		if (ray->slide == X_SLIDE)
			ray->map.x += ray->r_dir.x;
		if (ray->slide == Y_SLIDE)
			ray->map.y += ray->r_dir.y;
	}
}

void	do_raycasting(t_ray *ray, t_fpos *r_pos, t_fpos *r_side)
{
	double	r_tan;

	r_tan = tan(deg_to_rad(ray->r_angle));
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
