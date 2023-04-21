/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:45:46 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 13:35:01 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_player_data(t_data *data, char c, t_pos cur)
{
	data->ray.p_pos.x = cur.x * MAP_SCALE + MAP_SCALE / 2;
	data->ray.p_pos.y = cur.y * MAP_SCALE + MAP_SCALE / 2;
	data->map.has_player = true;
	if (c == P_E)
		data->ray.p_angle = 0;
	else if (c == P_N)
		data->ray.p_angle = 90;
	else if (c == P_W)
		data->ray.p_angle = 180;
	else if (c == P_S)
		data->ray.p_angle = 270;
}

static void	check_objects_on_map(t_data *data, t_map *map)
{
	t_pos	cur;
	char	c;

	cur.y = 0;
	while (cur.y < map->size.h)
	{
		cur.x = 0;
		while (cur.x < map->size.w)
		{
			c = map->array[cur.y][cur.x];
			if (c == P_N || c == P_S || c == P_W || c == P_E)
			{
				if (map->has_player == true)
					end_program(data, TOO_MUCH_PLAYER, TO_MUCH_PLAYER_MSG);
				set_player_data(data, c, cur);
				map->array[cur.y][cur.x] = EMPTY;
			}
			else if (c != WALL && c != EMPTY && c != ' ')
				end_program(data, MAP_UNDEF_CHAR, MAP_UNDEF_CHAR_MSG);
			cur.x++;
		}
		cur.y++;
	}
}

static void	check_invalid_spaces(t_data *data, t_map *map)
{
	t_pos	cur;

	cur.y = 0;
	while (cur.y < map->size.h)
	{
		cur.x = 0;
		while (cur.x < map->size.w)
		{
			if (map->array[cur.y][cur.x] == ' ')
				end_program(data, MAP_UNDEF_CHAR, MAP_UNDEF_CHAR_MSG);
			cur.x++;
		}
		cur.y++;
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
