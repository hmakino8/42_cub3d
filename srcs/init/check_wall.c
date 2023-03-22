/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:18:03 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 13:52:28 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_invalid_border_cell(t_data *data, char c)
{
	if (c != ' ' && c != CHECK && c != WALL)
		end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
}

void	check_adjacent(t_data *data, t_map *map, size_t x, size_t y)
{
	if (x > 0)
		check_invalid_border_cell(data, map->array[y][x - 1]);
	if (x < map->width - 1)
		check_invalid_border_cell(data, map->array[y][x + 1]);
	if (y > 0)
		check_invalid_border_cell(data, map->array[y - 1][x]);
	if (y < map->height - 1)
		check_invalid_border_cell(data, map->array[y + 1][x]);
	if (x > 0 && y > 0)
		check_invalid_border_cell(data, map->array[y - 1][x - 1]);
	if (x > 0 && y < map->height - 1)
		check_invalid_border_cell(data, map->array[y + 1][x - 1]);
	if (x < map->width - 1 && y < map->height - 1)
		check_invalid_border_cell(data, map->array[y + 1][x + 1]);
	if (x < map->width - 1 && y > 0)
		check_invalid_border_cell(data, map->array[y - 1][x + 1]);
}

void	check_horizontal_wall(t_data *data, t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1
			&& (map->array[y][x] == ' ' || map->array[y][x] == CHECK))
		{
			check_adjacent(data, map, x, y);
			map->array[y][x] = CHECK;
			x++;
		}
		if (x != map->width - 1 && map->array[y][x] != WALL)
			end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
		x = map->width - 1;
		while (x > 0 && (map->array[y][x] == ' ' || map->array[y][x] == CHECK))
		{
			check_adjacent(data, map, x, y);
			map->array[y][x] = CHECK;
			x--;
		}
		if (x != 0 && map->array[y][x] != WALL)
			end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
		y++;
	}
}

void	check_vertical_wall(t_data *data, t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height - 1
			&& (map->array[y][x] == ' ' || map->array[y][x] == CHECK))
		{
			check_adjacent(data, map, x, y);
			map->array[y][x] = CHECK;
			y++;
		}
		if (y != map->height - 1 && map->array[y][x] != WALL)
			end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
		y = map->height - 1;
		while (y > 0 && (map->array[y][x] == ' ' || map->array[y][x] == CHECK))
		{
			check_adjacent(data, map, x, y);
			map->array[y][x] = CHECK;
			y--;
		}
		if (y != 0 && map->array[y][x] != WALL)
			end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
		x++;
	}
}

void	check_map_wall(t_data *data, t_map *map)
{
	check_vertical_wall(data, map);
	check_horizontal_wall(data, map);
}
