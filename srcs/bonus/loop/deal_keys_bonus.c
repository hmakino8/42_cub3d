/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 17:19:21 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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
		dist->x *= - ((dist->x < 0) + (dist->x > 0)) * 8;
		dist->y *= - ((dist->y < 0) + (dist->y > 0)) * 8;
	}
	return (*dist);
}

bool	check_new_pos(t_pos new_pos, char **map)
{
	int	offset;

	offset = P_SIZE / 2;
	if (map[(new_pos.y - offset) / MAP_SCALE]
		[(new_pos.x - offset) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y - offset) / MAP_SCALE]
		[(new_pos.x + offset) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y + offset) / MAP_SCALE]
		[(new_pos.x - offset) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y + offset) / MAP_SCALE]
		[(new_pos.x + offset) / MAP_SCALE] == WALL)
		return (false);
	return (true);
}

t_pos	move(t_pos pos, double angle, double distance)
{
	t_pos	new_pos;

	new_pos.x = pos.x + distance * cos(deg_to_rad(angle));
	new_pos.y = pos.y + distance * -sin(deg_to_rad(angle));
	return (new_pos);
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
