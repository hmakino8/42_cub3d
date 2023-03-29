/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/29 17:04:48 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_move_key(int key)
{
	return (key == XK_w || key == XK_a || key == XK_s || key == XK_d);
}

bool	is_directory_key(int key)
{
	return (key == XK_Left || key == XK_Right);
}

t_pos	move(t_pos pos, double angle, double distance)
{
	t_pos	new_pos;

	new_pos.x = pos.x + distance * cos(deg_to_rad(angle));
	new_pos.y = pos.y + distance * -sin(deg_to_rad(angle));
	return (new_pos);
}

void	player_moves(int key, t_ray *ray, char **map)
{
	t_pos	p_pos;

	p_pos = ray->p_pos;
	if (key == XK_w)
		p_pos = move(p_pos, ray->p_angle, P_MOVE);
	else if (key == XK_a)
		p_pos = move(p_pos, ray->p_angle - 90.0, P_MOVE);
	else if (key == XK_s)
		p_pos = move(p_pos, ray->p_angle - 180.0, P_MOVE);
	else if (key == XK_d)
		p_pos = move(p_pos, ray->p_angle + 90.0, P_MOVE);
	if (map[p_pos.y / BPP][p_pos.x / BPP] == WALL)
		return ;
	ray->p_pos = p_pos;
}

void	player_change_direction(int key, t_ray *ray)
{
	if (key == XK_Left)
		ray->p_angle -= DICT_CHANGE;
	else
		ray->p_angle += DICT_CHANGE;
	ray->p_angle = fix_ang(ray->p_angle);
}

int	deal_keys(int key, t_data *data)
{
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	if (is_move_key(key))
		player_moves(key, &data->ray, data->map.array);
	if (is_directory_key(key))
		player_change_direction(key, &data->ray);
	return (0);
}
