/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/18 18:48:21 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static double	calculate_dist_to_wall(t_data *data, t_ray *ray)
{
	double	error;
	double	x_dist;

	(void)data;
	error = cos(deg_to_rad(ray->r_angle - ray->p_angle));
	x_dist = ray->r_pos.f_x - (double)ray->p_pos.x;
	return (x_dist / cos(deg_to_rad(ray->r_angle)) * error);
}

// static void	render_texture(int y, t_pos cur, t_rgb rgb, t_data *data, t_ray *ray)
// {
// 	if (y < ray->texture_hight)
// 	{
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, cur.x, cur.y + y, rgb.wall.color);
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, cur.x, cur.y - y, rgb.wall.color);
// 	}
// 	else
// 	{
// 		get_ceiling_floor_color(y, &rgb, data,ray);
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, cur.x, cur.y + y, rgb.floor.color);
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, cur.x, cur.y - y, rgb.ceiling.color);
// 	}
// }

static void	set_wall_size(int x, int w, t_data *data, t_ray *ray)
{
	//int		y;
	//t_pos	cur;
	//t_rgb	rgb;
	(void)x;
	(void)w;
	// cur.x = x;
	// cur.y = data->win_size.h / 2;
	ray->perp_w_dist = calculate_dist_to_wall(data, ray);
	ray->line_height = (double)data->win_size.h / ray->perp_w_dist * TEXTURE_SCALE;
	ray->w_start = lroundf(((double)data->win_size.h / 2.0)
			- (ray->line_height / 2.0));
	ray->w_end = lroundf(((double)data->win_size.h / 2.0)
			+ (ray->line_height / 2.0));
	ray->w_height = ray->w_end - ray->w_start;
	if (ray->slide == X_SLIDE)
		ray->wall_hit_x = (int)remainder(ray->r_pos.f_x, (double)MAP_SCALE);
	else
		ray->wall_hit_x = (int)remainder(ray->r_pos.f_y, (double)MAP_SCALE);
	// get_wall_color(&rgb.wall, data, ray);
	// y = 0;
	// while (cur.y + y < data->win_size.h)
	// {
	// 	render_texture(y, cur, rgb, data, ray);
	// 	y++;
	// }
}

static void	ray_collision_detection(double x, double w, t_data *data, t_ray *ray)
{
	init_ray(x, w, ray);
	while (data->map.array[ray->map.y][ray->map.x] != WALL)
	{
		do_raycasting(ray, &ray->r_pos, &ray->r_side);
		if (ray->slide == X_SLIDE)
			ray->map.x += ray->r_dir.x;
		if (ray->slide == Y_SLIDE)
			ray->map.y += ray->r_dir.y;
	}
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
	int	x;
	int	w;

	x = 0;
	w = data->win_size.w;
	while (x < w)
	{
		ray_collision_detection((double)x, (double)w, data, ray);
		set_wall_size(x + 1, w, data, ray);
		render_ray(data, ray, x);
		draw_ray_lines(data, ray, RAY);
		//render_ray_to_minimap(x, data, &data->ray);
		// if (x + 1 == w)
		// 	get_minimap_player_img(data);
		x++;
	}
}
