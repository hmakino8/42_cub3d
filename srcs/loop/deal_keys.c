/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:53:32 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 14:19:28 by pfrances         ###   ########.fr       */
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

void	player_moves(int key, t_pos *p_pos, char **map_array)
{
	int		adj;
	t_pos	new;
	t_pos	tmp;

	new = *p_pos;
	adj = PLAYER_SIZE / 2;
	if (key == XK_w)
	{
		new.y -= P_MOVE;
		adj *= -1;
	}
	if (key == XK_a)
	{
		new.x -= P_MOVE;
		adj *= -1;
	}
	if (key == XK_s)
		new.y += P_MOVE;
	if (key == XK_d)
		new.x += P_MOVE;
	tmp.y = (new.y + P_MOVE + adj) / BPP;
	tmp.x = (new.x + P_MOVE + adj) / BPP;
	if (map_array[tmp.y][tmp.x] == WALL)
		return ;
	*p_pos = new;
}

void	player_change_direction(int key, float *angle)
{
	if (key == XK_Left)
		*angle += DICT_CHANGE;
	else
		*angle -= DICT_CHANGE;
	*angle = fix_ang(*angle);
}

int	deal_keys(int key, t_data *data)
{
	t_player	*player;

	player = &data->player;
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	if (is_move_key(key))
		player_moves(key, &player->p_pos, data->map.array);
	if (is_directory_key(key))
		player_change_direction(key, &player->angle);
	return (0);
}
