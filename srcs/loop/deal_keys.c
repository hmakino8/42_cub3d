/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/03 20:51:26 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_new_pos(t_pos new_pos, char **map)
{
	if (map[(new_pos.y + (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP]
		[(new_pos.x + (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP] == WALL)
		return (false);
	else if (map[(new_pos.y + (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP]
		[(new_pos.x - (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP] == WALL)
		return (false);
	else if (map[(new_pos.y - (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP]
		[(new_pos.x + (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP] == WALL)
		return (false);
	else if (map[(new_pos.y - (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP]
		[(new_pos.x - (PLAYER_SIZE / 2) * BPP / C_SIZE) / BPP] == WALL)
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

void	do_action(int key, t_ray *ray, char **map)
{
	t_pos	p_pos;

	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
	{
		if (key == XK_w)
			p_pos = move(ray->p_pos, ray->p_angle, P_MOVE);
		else if (key == XK_a)
			p_pos = move(ray->p_pos, ray->p_angle + 90.0, P_MOVE);
		else if (key == XK_s)
			p_pos = move(ray->p_pos, ray->p_angle - 180.0, P_MOVE);
		else if (key == XK_d)
			p_pos = move(ray->p_pos, ray->p_angle - 90.0, P_MOVE);
		if (check_new_pos(p_pos, map))
			ray->p_pos = p_pos;
	}
	else if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			ray->p_angle += DICT_CHANGE;
		else if (key == XK_Right)
			ray->p_angle -= DICT_CHANGE;
		ray->p_angle = fix_ang(ray->p_angle);
	}
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
