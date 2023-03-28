/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/28 15:30:01 by pfrances         ###   ########.fr       */
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

void	player_moves(int key, t_data *data)
{
	t_pos	new_pos;

	new_pos = data->ray.p_pos;
	if (key == XK_w)
		new_pos.y -= P_MOVE;
	else if (key == XK_a)
		new_pos.x -= P_MOVE;
	else if (key == XK_s)
		new_pos.y += P_MOVE;
	else if (key == XK_d)
		new_pos.x += P_MOVE;
	if (data->map.array[new_pos.y / BPP][new_pos.x / BPP] == WALL)
		return ; // check after
	data->ray.p_pos = new_pos;
}

void	player_change_direction(int key, t_ray *ray)
{
	if (key == XK_Left)
		ray->p_angle += DICT_CHANGE;
	else
		ray->p_angle -= DICT_CHANGE;
	ray->p_angle = fix_ang(ray->p_angle);
}

int	deal_keys(int key, t_data *data)
{
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	if (is_move_key(key))
		player_moves(key, data);
	if (is_directory_key(key))
		player_change_direction(key, &data->ray);
	return (0);
}
