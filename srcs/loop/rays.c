/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/02 16:59:19 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray(t_pos p_pos, t_ray *ray)
{
	ray->hit_wall = false;
	ray->r_delta.f_x = cos(deg_to_rad(ray->r_angle));
	ray->r_delta.f_y = -sin(deg_to_rad(ray->r_angle));
	ray->r_pos.x = p_pos.x;
	ray->r_pos.y = p_pos.y;
	if (ray->r_delta.f_x > 0)
		ray->r_dir.x = 1;
	else if (ray->r_delta.f_x < 0)
		ray->r_dir.x = -1;
	if (ray->r_delta.f_y > 0)
		ray->r_dir.y = 1;
	else if (ray->r_delta.f_y < 0)
		ray->r_dir.y = -1;
	ray->p_side = get_side(ray->p_pos, ray->r_delta);
	ray->r_side = ray->p_side;
	ray->slide_cnt.x = 0;
	ray->slide_cnt.y = 0;
}

void	check_wall(char **map, t_ray *ray)
{
	t_pos	cell;

	cell.x = (ray->r_pos.x + ray->r_dir.x) / BPP;
	cell.y = (ray->r_pos.y + ray->r_dir.y) / BPP;
	if (map[cell.y][cell.x] == WALL)
	{
		ray->hit_wall = true;
		if (ray->slide == X_SLIDE)
			ray->wall_hit_x = ray->r_pos.y % BPP;
		else
			ray->wall_hit_x = ray->r_pos.x % BPP;
	}
}

void	calculate_ray_size(t_data *data, t_ray *ray)
{
	ray->perp_w_dist = roundf(((ray->r_pos.x - ray->p_pos.x) * ray->r_delta.f_x
			+ (ray->r_pos.y - ray->p_pos.y) * ray->r_delta.f_y)
		* cos(deg_to_rad(fix_ang(ray->r_angle - ray->p_angle))));
	ray->line_height = lroundf((double)(data->win_size.h * BPP) / ray->perp_w_dist);
	ray->w_start = lroundf(((double)data->win_size.h / 2.0)
			- ((double)ray->line_height / 2.0));
	ray->w_end = lroundf(((double)data->win_size.h / 2.0)
			+ ((double)ray->line_height / 2.0));
	ray->w_size.h = ray->w_end - ray->w_start;
}

void	render_ray(t_data *data, t_ray *ray, int x)
{
	t_pos	pos;

	pos.y = 0;
	pos.x = x;
	while (pos.y < data->win_size.h)
	{
		if (pos.y > 0 && pos.y >= ray->w_start && pos.y <= ray->w_end)
			put_text_to_screen(data, ray, pos);
		else if (pos.y < ray->w_start)
			put_pixel_to_img(&data->img.screen, pos,
				data->color.ceiling.bit_color);
		else
			put_pixel_to_img(&data->img.screen, pos,
				data->color.floor.bit_color);
		pos.y++;
	}
}

void	draw_rays(t_data *data, t_ray *ray)
{
	double	i;

	i = 0;
	while (i < data->win_size.w)
	{
		ray->r_angle = fix_ang(ray->p_angle + FOV / 2.0 - (i * FOV)
			/ (double)data->win_size.w);
		init_ray(ray->p_pos, ray);
		while (ray->hit_wall == false)
		{
			set_next_slide(ray);
			update_ray_pos(ray);
			check_wall(data->map.array, ray);
		}
		calculate_ray_size(data, ray);
		render_ray(data, ray, i);
		draw_ray_lines(data, ray, VIEW_POINT);
		i++;
	}
}
