/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:47:12 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 08:47:39 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*skip_head_tail_empty_lines(char *content)
{
	char	*result;
	size_t	head;
	size_t	tail;
	size_t	to_keep_count;

	to_keep_count = ft_strlen(content);
	head = 0;
	while (content[head] == '\n')
	{
		head++;
		to_keep_count--;
	}
	if (content[head] == '\0')
	{
		free(content);
		return (NULL);
	}
	tail = ft_strlen(content);
	while (tail > 0 && content[--tail] == '\n')
		to_keep_count--;
	result = ft_strndup(&content[head], to_keep_count);
	free(content);
	return (result);
}

bool	check_empty_line(char *map)
{
	size_t	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			if (i == 0 || map[i + 1] == '\n' || map[i + 1] == '\0')
				return (false);
		}
		i++;
	}
	return (true);
}

void	get_map_content(t_data *data, size_t i)
{
	char *map_content;

	map_content = ft_strdup(&data->file_content[i]);
	free(data->file_content);
	if (map_content == NULL)
		end_program(data, MALLOC_FAILED, FAILED_ON_MALLOC_MSG);
	map_content = skip_head_tail_empty_lines(map_content);
	if (map_content == NULL)
		end_program(data, EMPTY_MAP, EMPTY_MAP_MSG);
	if (check_empty_line(map_content) == false)
	{
		free(map_content);
		end_program(data, HAS_EMPTY_LINE, HAS_EMPTY_LINE_MSG);
	}
	data->map.array = ft_split(map_content, '\n');
	if (data->map.array == NULL)
		end_program(data, MALLOC_FAILED, FAILED_ON_MALLOC_MSG);
}
