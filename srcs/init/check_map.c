/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:45:46 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/26 14:22:16 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player_data(t_data *data, char c, t_pos pos)
{
	data->player.pos_pxl.x = (pos.x * BPP) + (BPP / 2);
	data->player.pos_pxl.y = (pos.y * BPP) + (BPP / 2);
	data->map.has_player = true;
	if (c == P_E)
		data->player.angle = 0;
	else if (c == P_N)
		data->player.angle = 90;
	else if (c == P_W)
		data->player.angle = 180;
	else if (c == P_S)
		data->player.angle = 270;
}

void	check_objects_on_map(t_data *data, t_map *map)
{
	t_pos	pos;
	char	c;

	pos.y = 0;
	while (pos.y < map->height)
	{
		pos.x = 0;
		while (pos.x < map->width)
		{
			c = map->array[pos.y][pos.x];
			if (c == P_N || c == P_S || c == P_W || c == P_E)
			{
				if (map->has_player == true)
					end_program(data, TOO_MUCH_PLAYER, TO_MUCH_PLAYER_MSG);
				set_player_data(data, c, pos);
				map->array[pos.y][pos.x] = EMPTY;
			}
			else if (c != WALL && c != EMPTY && c != ' ')
				end_program(data, MAP_UNDEF_CHAR, MAP_UNDEF_CHAR_MSG);
			pos.x++;
		}
		pos.y++;
	}
}

void	check_invalid_spaces(t_data *data, t_map *map)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < map->height)
	{
		pos.x = 0;
		while (pos.x < map->width)
		{
			if (map->array[pos.y][pos.x] == ' ')
				end_program(data, MAP_UNDEF_CHAR, MAP_UNDEF_CHAR_MSG);
			pos.x++;
		}
		pos.y++;
	}
}

void	check_map(t_data *data, t_map *map)
{
	map->has_player = false;
	check_objects_on_map(data, map);
	if (map->has_player == false)
		end_program(data, HAS_NO_PLAYER, HAS_NO_PLAYER_MSG);
	check_map_wall(data, map);
	check_invalid_spaces(data, map);
}
