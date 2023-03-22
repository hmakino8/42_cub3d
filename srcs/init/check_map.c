/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:45:46 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 12:09:56 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player_data(t_data *data, char c, size_t x, size_t y)
{
	data->player.x = (x * CUBE_SIZE) + (CUBE_SIZE / 2);
	data->player.y = (y * CUBE_SIZE) + (CUBE_SIZE / 2);
	data->map.has_player = true;
	if (c == PLAYER_E)
		data->player.angle = 0;
	else if (c == PLAYER_N)
		data->player.angle = 90;
	else if (c == PLAYER_W)
		data->player.angle = 180;
	else if (c == PLAYER_S)
		data->player.angle = 270;
}

void	check_objects_on_map(t_data *data, t_map *map)
{
	size_t	x;
	size_t	y;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->array[y][x];
			if (c == PLAYER_N || c == PLAYER_S || c == PLAYER_E || c == PLAYER_W)
			{
				if (map->has_player == true)
					end_program(data, TOO_MUCH_PLAYER, TO_MUCH_PLAYER_MSG);
				set_player_data(data, c, x, y);
				map->array[y][x] = EMPTY;
			}
			else if (c != WALL && c != EMPTY && c != ' ')
				end_program(data, MAP_UNDEFINED_CHARACTER, MAP_UNDEFINED_CHARACTER_MSG);
			x++;
		}
		y++;
	}
}

void	check_invalid_spaces(t_data *data, t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->array[y][x] == ' ')
				end_program(data, MAP_UNDEFINED_CHARACTER, MAP_UNDEFINED_CHARACTER_MSG);
			x++;
		}
		y++;
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
