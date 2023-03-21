/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:46:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/19 18:16:33 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_objects_on_map(t_data *data, char c, size_t x, size_t y)
{
	if ((x == 0 && c != WALL)
		|| (x == data->map.width - 1 && c != WALL))
		end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
	else if (c == WALL || c == EMPTY)
		;
	else if (c == PLAYER_N || c == PLAYER_S || c == PLAYER_E || c == PLAYER_W)
	{
		if (data->map.has_player == true)
			end_program(data, TOO_MUCH_PLAYER, TO_MUCH_PLAYER_MSG);
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
		data->map.array[y][x] = EMPTY;
	}
	else
		end_program(data, UNDEFINED_CHARACTER, UNDEFINED_CHARACTER_MSG);
}

void	check_line_content(t_data *data, char *line, size_t y)
{
	size_t	x;

	x = 0;
	while (x < data->map.width)
	{
		check_objects_on_map(data, line[x], x, y);
		x++;
	}
}

void	check_there_are_only_walls(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != WALL)
			end_program(data, NOT_BORDERED_BY_WALL, NOT_BORDERED_BY_WALL_MSG);
		i++;
	}
}

void	content_final_check(t_data *data)
{
	if (data->map.height < HEIGHT_MIN)
		end_program(data, WRONG_SHAPE, WRONG_SHAPE_MSG);
	if (data->map.has_player == false)
		end_program(data, HAS_NO_PLAYER, HAS_NO_PLAYER_MSG);
}

void	check_content(t_data *data)
{
	size_t	i;

	data->map.width = ft_strlen(data->map.array[0]);
	if (data->map.width < WITDH_MIN)
		end_program(data, WRONG_SHAPE, WRONG_SHAPE_MSG);
	i = 0;
	data->map.has_player = false;
	while (data->map.array[i] != NULL)
	{
		if (i != 0 && ft_strlen(data->map.array[i]) != data->map.width)
			end_program(data, WRONG_SHAPE, WRONG_SHAPE_MSG);
		if (i == 0 || data->map.array[i + 1] == NULL)
			check_there_are_only_walls(data, data->map.array[i]);
		else
			check_line_content(data, data->map.array[i], i);
		i++;
	}
	data->map.height = i;
	content_final_check(data);
}
