/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:37:51 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/21 15:39:16 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_map_height_width(t_map *map)
{
	int	line_len;

	map->size.w = 0;
	map->size.h = 0;
	while (map->array[map->size.h] != NULL)
	{
		line_len = ft_strlen(map->array[map->size.h]);
		if (line_len > map->size.w)
			map->size.w = line_len;
		map->size.h++;
	}
}

void	resize_line(t_data *data, char **line_adress, size_t witdh)
{
	char	*resized_line;
	size_t	i;

	resized_line = malloc(sizeof(char) * (witdh + 1));
	if (resized_line == NULL)
		end_program(data, RESIZE_MALLOC_FAILED, FAILED_ON_MALLOC_MSG);
	ft_strlcpy(resized_line, *line_adress, witdh);
	i = ft_strlen(*line_adress);
	while (i < witdh)
	{
		resized_line[i] = ' ';
		i++;
	}
	resized_line[i] = '\0';
	free(*line_adress);
	*line_adress = resized_line;
}

void	init_map(t_data *data, t_map *map)
{
	int	y;

	set_map_height_width(map);
	if (map->size.h < HEIGHT_MIN || map->size.w < WITDH_MIN)
		end_program(data, WRONG_SHAPE, WRONG_SHAPE_MSG);
	y = 0;
	while (map->array[y] != NULL)
	{
		if ((int)ft_strlen(map->array[y]) < map->size.w)
			resize_line(data, &map->array[y], map->size.w);
		y++;
	}
	map->mini_map_size.h = map->size.h * C_SIZE;
	map->mini_map_size.w = map->size.w * C_SIZE;
}
