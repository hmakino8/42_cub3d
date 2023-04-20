/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/20 17:46:09by hiroaki          ###   ########.fr       */
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

void	set_wall_size(t_data *data, t_ray *ray)
{
	ray->perp_w_dist = calculate_dist_to_wall(ray);
	if (data->is_here_door && ray->perp_w_dist < ray->perp_w_dist_min)
	{
		ray->perp_w_dist_min = ray->perp_w_dist;
		printf("%f\n",ray->perp_w_dist_min);
	}
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

static void	ray_collision_detection(int x, t_data *data, t_ray *ray)
{
	while (data->map.array[ray->map.y][ray->map.x] != WALL)
	{
		do_raycasting(ray, &ray->r_pos, &ray->r_side);
		if (ray->slide == X_SLIDE)
			ray->map.x += ray->r_dir.x;
		if (ray->slide == Y_SLIDE)
			ray->map.y += ray->r_dir.y;
		data->is_here_door = false;
		data->is_here_door =  data->map.array[ray->map.y][ray->map.x] == DOOR;
		if (data->is_here_door)
		{
			set_wall_size(data, ray);
			render_door(data, ray, x);
		}
	}
}

void	render_door(t_data *data, t_ray *ray, int x)
{
	t_pos		pos;
	t_rgb_info	rgb;

	pos.y = ray->w_start;
	pos.x = x;
	while (pos.y > 0 && pos.y <= ray->w_end && pos.y < data->win_size.h)
	{
		put_door_to_screen(data, ray, pos);
		pos.y++;
	}
}

void	render_ray(t_data *data, t_ray *ray, int x)
{
	t_pos		pos;
	t_rgb_info	rgb;

	pos.y = 0;
	pos.x = x;
	while (pos.y < data->win_size.h)
	{
		if (pos.y > 0 && pos.y >= ray->w_start && pos.y <= ray->w_end)
			put_text_to_screen(data, ray, pos);
		else
		{
			if (pos.y < ray->w_start)
			{
				rgb.ratio = ray->line_height / (double)data->win_size.h;
				brightness_control(data->color.ceiling.rgb, &rgb);
			}
			else
			{
				rgb.ratio = (double)pos.y / (double)data->win_size.h * 0.3;
				brightness_control(data->color.floor.rgb, &rgb);
			}
			put_pixel_to_img(&data->img.screen, pos, rgb.rgb);
		}
		pos.y++;
	}
}

void	draw_rays(t_data *data, t_ray *ray)
{
	int	x;
	int	w;

	x = 0;
	w = data->win_size.w;
	data->i = 0;
	data->ray.perp_w_dist_min = DBL_MAX;
	while (x < w)
	{
		init_ray((double)x, (double)w, ray);
		ray_collision_detection(x, data, ray);
		set_wall_size(data, ray);
		render_ray(data, ray, x);
		if (BONUS)
			draw_ray_lines(data, ray, RAY);
		x++;
	}
	int i = 0;
	int	active;
	active = data->map.size.h * MAP_SCALE/10;
	if (data->ray.perp_w_dist_min > active)
	{
		while (i < data->i)
		{
			put_pixel_to_img(&data->img.screen, data->save_door_pos[i], data->save_door_color[i]);
			i++;
		}
	}
}
