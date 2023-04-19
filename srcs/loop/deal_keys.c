/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/19 18:20:16 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_new_pos(t_pos new_pos, char **map)
{
	if (map[(new_pos.y + (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE]
		[(new_pos.x + (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y + (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE]
		[(new_pos.x - (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y - (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE]
		[(new_pos.x + (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE] == WALL)
		return (false);
	else if (map[(new_pos.y - (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE]
		[(new_pos.x - (P_SIZE / 2) * MAP_SCALE / C_SIZE) / MAP_SCALE] == WALL)
		return (false);
	return (true);
}

double	get_move_angle(int key, t_ray *ray)
{
	double	angle;

	angle = ray->p_angle;
	if (key == XK_a)
		angle += 90;
	if (key == XK_s)
		angle -= 180;
	if (key == XK_d)
		angle -= 90;
	return (fix_ang(angle));
}

int	deal_keys(int key, void *ptr)
{
	t_data	*data;
	t_ray	*ray;

	data = (t_data *)ptr;
	ray = &data->ray;
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
		check_wall_collison(data, P_MOVE, get_move_angle(key, ray));
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
