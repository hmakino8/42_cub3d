/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/18 18:41:57 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_pos	move_dist(int key, t_ray *ray);
static t_pos	wall_collision(\
					t_pos *dist, char **map_array, t_ray *ray);

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

static t_pos	\
	wall_collision(t_pos *dist, char **map_array, t_ray *ray)
{
	int		offset;
	t_pos	top;
	t_pos	down;

	offset = PLAYER_SIZE / 2;
	top.x = (ray->p_pos.x + dist->x - offset) / MAP_SCALE;
	top.y = (ray->p_pos.y + dist->y - offset) / MAP_SCALE;
	down.x = (ray->p_pos.x + dist->x + offset) / MAP_SCALE;
	down.y = (ray->p_pos.y + dist->y + offset) / MAP_SCALE;
	if (map_array[top.y][top.x] == WALL || \
		map_array[down.y][down.x] == WALL)
	{
		dist->x *= - ((dist->x < 0) + (dist->x > 0)) * 8;
		dist->y *= - ((dist->y < 0) + (dist->y > 0)) * 8;
	}
	return (*dist);
}

bool	check_new_pos(t_pos new_pos, char **map)
{
	int	offset;

	offset = PLAYER_SIZE / 2;
	if (map[(new_pos.y - offset) / MAP_SCALE][(new_pos.x - offset) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y - offset) / MAP_SCALE][(new_pos.x + offset) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y + offset) / MAP_SCALE][(new_pos.x - offset) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y + offset) / MAP_SCALE][(new_pos.x + offset) / MAP_SCALE] == WALL)
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

void	deviation(t_ray *ray, t_pos pos, char **map)
{
	double	angle;
	int		i;
	t_pos	new_pos;

	i = 0;
	angle = ray->p_angle;
	new_pos = pos;
	while (check_new_pos(new_pos, map) == false)
	{
		new_pos = move(ray->p_pos, angle, P_MOVE);
		angle = fix_ang(angle + 1.0);
		i++;
	}
	angle = ray->p_angle;
	new_pos = pos;
	while (check_new_pos(new_pos, map) == false)
	{
		new_pos = move(ray->p_pos, angle, P_MOVE);
		angle = fix_ang(angle - 1.0);
		i--;
	}
	if (i > 0)
		ray->p_angle = fix_ang(ray->p_angle - 1.0);
	else
		ray->p_angle = fix_ang(ray->p_angle + 1.0);
}

void	do_action(int key, t_ray *ray, char **map)
{
	//t_pos	p_pos;
	t_pos	dist;

	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
	{
		dist = move_dist(key, ray);
		dist = wall_collision(&dist, map, ray);
		ray->p_pos.x += dist.x;
		ray->p_pos.y += dist.y;
		// if (key == XK_w)
		// 	p_pos = move(ray->p_pos, ray->p_angle, P_MOVE);
		// else if (key == XK_a)
		// 	p_pos = move(ray->p_pos, ray->p_angle + 90.0, P_MOVE);
		// else if (key == XK_s)
		// 	p_pos = move(ray->p_pos, ray->p_angle - 180.0, P_MOVE);
		// else if (key == XK_d)
		// 	p_pos = move(ray->p_pos, ray->p_angle - 90.0, P_MOVE);
		// if (check_new_pos(p_pos, map))
		// 	ray->p_pos = p_pos;
		// else
		// 	deviation(ray, p_pos, map);
	}
	else if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			ray->p_angle += DICT_CHANGE;
		else if (key == XK_Right)
			ray->p_angle -= DICT_CHANGE;
	}
	ray->p_angle = fix_ang(ray->p_angle);
}

int	deal_keys(int key, void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	do_action(key, &data->ray, data->map.array);
	return (0);
}
