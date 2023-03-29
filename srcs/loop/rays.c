/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/29 22:47:30 by pfrances         ###   ########.fr       */
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
		ray->hit_wall = true;
}

void	calculate_ray_size(t_data *data, t_ray *ray)
{
	ray->perp_wall_dist = fabs((ray->r_pos.x - ray->p_pos.x)
			* cos(deg_to_rad(ray->r_angle))
			+ (ray->r_pos.y - ray->p_pos.y)
			* -sin(deg_to_rad(ray->r_angle)))
		* cos(deg_to_rad(ray->r_angle - ray->p_angle));
	ray->line_height = ((data->win_size.h * BPP) / (ray->perp_wall_dist));
	ray->w_start = -ray->line_height / 2 + data->win_size.h / 2;
	ray->w_end = ray->line_height / 2 + data->win_size.h / 2;
	if (ray->w_start < 0)
		ray->w_start = 0;
	if (ray->w_end >= data->win_size.h)
		ray->w_end = data->win_size.h - 1;
}

void	render_ray(t_data *data, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < data->win_size.h)
	{
		if (x < data->map.mini_map_size.w + MINI_MAP_BORDER * 2
			&& y < data->map.mini_map_size.h + MINI_MAP_BORDER * 2)
			;
		else if (y >= ray->w_start && y <= ray->w_end && ray->slide == X_SLIDE)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF0000);
		else if (y >= ray->w_start && y <= ray->w_end && ray->slide == Y_SLIDE)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x8F0000);
		else if (y < ray->w_start)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y,
				data->color.ceiling.bit_color);
		else
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y,
				data->color.floor.bit_color);
		y++;
	}
}

void	draw_rays(t_data *data, t_ray *ray)
{
	double	i;

	i = 0;
	while (i < data->win_size.w)
	{
		ray->r_angle = ray->p_angle - FOV / 2.0 + i
			/ (double)data->win_size.w * FOV;
		init_ray(ray->p_pos, ray);
		while (ray->hit_wall == false)
		{
			set_next_slide(ray);
			update_ray_pos(ray);
			check_wall(data->map.array, ray);
		}
		calculate_ray_size(data, ray);
		render_ray(data, ray, i);
		i++;
	}
}
