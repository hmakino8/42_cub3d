/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 23:01:48 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_pos	move_dist(int key, t_ray *ray)
{
	double	dir;
	t_pos	dist;

	dir = ray->p_angle;
	if (key == XK_a)
		dir += 90;
	if (key == XK_s)
		dir -= 180;
	if (key == XK_d)
		dir -= 90;
	dist.x = P_MOVE * cos(deg_to_rad(dir));
	dist.y = P_MOVE * -sin(deg_to_rad(dir));
	return (dist);
}

static t_pos	wall_check(t_data *data, t_pos *dist, t_ray *ray)
{
	int		offset;
	t_pos	top;
	t_pos	down;

	offset = P_SIZE / 2;
	top.x = (ray->p_pos.x + dist->x - offset) / MAP_SCALE;
	top.y = (ray->p_pos.y + dist->y - offset) / MAP_SCALE;
	down.x = (ray->p_pos.x + dist->x + offset) / MAP_SCALE;
	down.y = (ray->p_pos.y + dist->y + offset) / MAP_SCALE;
	if (data->map.array[top.y][top.x] == WALL
		|| data->map.array[down.y][down.x] == WALL)
	{
		dist->x = 0;
		dist->y = 0;
	}
	return (*dist);
}

int	deal_keys(int key, void *ptr)
{
	t_data	*data;
	t_ray	*ray;
	t_pos	dist;

	data = (t_data *)ptr;
	ray = &data->ray;
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
	{
		dist = move_dist(key, ray);
		dist = wall_check(data, &dist, ray);
		ray->p_pos.x += dist.x;
		ray->p_pos.y += dist.y;
	}
	else if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			ray->p_angle += DICT_CHANGE;
		else if (key == XK_Right)
			ray->p_angle -= DICT_CHANGE;
	}
	ray->p_angle = fix_ang(ray->p_angle);
	return (0);
}
