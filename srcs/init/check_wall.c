/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:18:03 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 11:13:17 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_invalid_border_cell(t_data *data, char c)
{
	if (c != ' ' && c != CHECK && c != WALL)
		end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
}

void	check_adjacent(t_data *data, t_map *map, int x, int y)
{
	if (x > 0)
		check_invalid_border_cell(data, map->array[y][x - 1]);
	if (x < map->size.w - 1)
		check_invalid_border_cell(data, map->array[y][x + 1]);
	if (y > 0)
		check_invalid_border_cell(data, map->array[y - 1][x]);
	if (y < map->size.h - 1)
		check_invalid_border_cell(data, map->array[y + 1][x]);
	map->array[y][x] = CHECK;
}

void	check_map_wall(t_data *data, t_map *map)
{
	t_pos	pos;

	pos.y = 0;
	while (pos.y < map->size.h)
	{
		pos.x = 0;
		while (pos.x < map->size.w)
		{
			if (map->array[pos.y][pos.x] == ' ')
				check_adjacent(data, map, pos.x, pos.y);
			else if (pos.y == 0 || pos.y == map->size.h - 1)
			{
				if (map->array[pos.y][pos.x] != WALL
					&& map->array[pos.y][pos.x] != CHECK)
						end_program(data, NOT_BORDERED_BY_WALL,
							NOT_BORDERED_BY_WALL_MSG);
			}
			pos.x++;
		}
		pos.y++;
	}
}
