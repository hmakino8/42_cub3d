/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:18:03 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 10:16:58 by pfrances         ###   ########.fr       */
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
	if (x > 0 && y > 0)
		check_invalid_border_cell(data, map->array[y - 1][x - 1]);
	if (x > 0 && y < map->size.h - 1)
		check_invalid_border_cell(data, map->array[y + 1][x - 1]);
	if (x < map->size.w - 1 && y < map->size.h - 1)
		check_invalid_border_cell(data, map->array[y + 1][x + 1]);
	if (x < map->size.w - 1 && y > 0)
		check_invalid_border_cell(data, map->array[y - 1][x + 1]);
}

void	check_horizontal_wall(t_data *data, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->size.h)
	{
		x = 0;
		while (x < map->size.w - 1
			&& (map->array[y][x] == ' ' || map->array[y][x] == CHECK))
		{
			check_adjacent(data, map, x, y);
			map->array[y][x] = CHECK;
			x++;
		}
		if (x != map->size.w - 1 && map->array[y][x] != WALL)
			end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
		x = map->size.w - 1;
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
	int	x;
	int	y;

	x = 0;
	while (x < map->size.w)
	{
		y = 0;
		while (y < map->size.h - 1
			&& (map->array[y][x] == ' ' || map->array[y][x] == CHECK))
		{
			check_adjacent(data, map, x, y);
			map->array[y][x] = CHECK;
			y++;
		}
		if (y != map->size.h - 1 && map->array[y][x] != WALL)
			end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
		y = map->size.h - 1;
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
