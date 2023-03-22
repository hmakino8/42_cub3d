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
	size_t	line_len;
	size_t	y;

	map->width = 0;
	y = 0;
	while (map->array[y] != NULL)
	{
		line_len = ft_strlen(map->array[y]);
		if (line_len > map->width)
			map->width = line_len;
		y++;
	}
	map->height = y;
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
	size_t	y;

	set_map_height_width(map);
	if (map->height < HEIGHT_MIN || map->width < WITDH_MIN)
		end_program(data, WRONG_SHAPE, WRONG_SHAPE_MSG);
	y = 0;
	while (map->array[y] != NULL)
	{
		if (ft_strlen(map->array[y]) < map->width)
			resize_line(data, &map->array[y], map->width);
		y++;
	}
}
