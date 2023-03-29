/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/29 12:14:50 by pfrances         ###   ########.fr       */
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

t_pos	player_moves(int key, t_pos p_pos, char **map)
{
	if (key == XK_w)
	{
		p_pos.y -= P_MOVE + PLAYER_SIZE / 2;
		while (map[p_pos.y / BPP][p_pos.x / BPP] == WALL)
			p_pos.y++;
		p_pos.y += PLAYER_SIZE / 2;
	}
	else if (key == XK_a)
	{
		p_pos.x -= P_MOVE + PLAYER_SIZE / 2;
		while (map[p_pos.y / BPP][p_pos.x / BPP] == WALL)
			p_pos.x++;
		p_pos.x += PLAYER_SIZE / 2;
	}
	else if (key == XK_s)
	{
		p_pos.y += P_MOVE + PLAYER_SIZE / 2;
		while (map[p_pos.y / BPP][p_pos.x / BPP] == WALL)
			p_pos.y--;
		p_pos.y -= PLAYER_SIZE / 2;
	}
	else if (key == XK_d)
	{
		p_pos.x += P_MOVE + PLAYER_SIZE / 2;
		while (map[p_pos.y / BPP][p_pos.x / BPP] == WALL)
			p_pos.x--;
		p_pos.x -= PLAYER_SIZE / 2;
	}
	return (p_pos);
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
		data->ray.p_pos = player_moves(key, data->ray.p_pos, data->map.array);
	if (is_directory_key(key))
		player_change_direction(key, &data->ray);
	return (0);
}
