/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 18:00:15 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	calculate_dist_to_wall(t_ray *ray)
{
	double	error;
	double	x_dist;

	error = cos(deg_to_rad(ray->r_angle - ray->p_angle));
	x_dist = ray->r_pos.f_x - (double)ray->p_pos.x;
	return (x_dist / cos(deg_to_rad(ray->r_angle)) * error);
}

static void	set_wall_size(t_data *data, t_ray *ray)
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

static void	ray_collision_detection(t_data *data, t_ray *ray)
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

static void	render_ray(t_data *data, t_ray *ray, int x)
{
	t_pos		pos;

	pos.y = 0;
	pos.x = x;
	while (pos.y < data->win_size.h)
	{
		if (pos.y > 0 && pos.y >= ray->w_start && pos.y <= ray->w_end)
			put_text_to_screen(data, ray, pos);
		else if (pos.y < ray->w_start)
			put_pixel_to_img(&data->img.screen, pos, data->color.ceiling.rgb);
		else
			put_pixel_to_img(&data->img.screen, pos, data->color.floor.rgb);
		pos.y++;
	}
}

void	draw_rays(t_data *data, t_ray *ray)
{
	int	x;
	int	w;

	x = 0;
	w = data->win_size.w;
	while (x < w)
	{
		init_ray((double)x, (double)w, ray);
		ray_collision_detection(data, ray);
		set_wall_size(data, ray);
		render_ray(data, ray, x);
		x++;
	}
}
