/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/29 12:47:38 by pfrances         ###   ########.fr       */
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
	cell.y = (ray->r_pos.y +  ray->r_dir.y) / BPP;
	if (map[cell.y][cell.x] == WALL)
		ray->hit_wall = true;
}

void	update_ray_pos(t_ray *ray)
{
	ray->r_pos = ray->p_pos;
	if (ray->slide == X_SLIDE)
	{
		ray->r_pos.x += (ray->p_side.x + ray->slide_cnt.x * BPP) * ray->r_dir.x;
		ray->r_pos.y += lround((double)(ray->p_side.x + ray->slide_cnt.x * BPP)
				* (ray->r_delta.f_y / fabs(ray->r_delta.f_x)));
		ray->slide_cnt.x++;
	}
	else if (ray->slide == Y_SLIDE)
	{
		ray->r_pos.x += lround((double)(ray->p_side.y + ray->slide_cnt.y * BPP)
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

void	draw_rays(t_data *data, t_ray *ray)
{
	double	i;

	i = 0;
	while (i < data->win_size.w)
	{
		ray->r_angle = ray->p_angle - FOV / 2.0 + i / (double)data->win_size.w * FOV;
		init_ray(ray->p_pos, ray);
		while (ray->hit_wall == false)
		{
			set_next_slide(ray);
			update_ray_pos(ray);
			check_wall(data->map.array, ray);
		}
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img.player.mlx_img,
				ray->r_pos.x - PLAYER_SIZE / 2, ray->r_pos.y - PLAYER_SIZE / 2);
		i++;
	}
}
