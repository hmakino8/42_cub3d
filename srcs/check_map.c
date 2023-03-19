/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:45:46 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/19 18:10:09 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_filename(t_data *data, char *str)
{
	size_t	filename_len;
	size_t	extension_len;
	char	*filename;

	filename = ft_strrchr(str, '/');
	if (filename == NULL)
		filename = str;
	else
		filename++;
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(MAP_FILE_EXTENSION);
	if (filename_len <= extension_len)
		end_program(data, WRONG_MAP_NAME, WRONG_MAP_NAME_MSG);
	if (ft_strncmp(MAP_FILE_EXTENSION,
			&filename[filename_len - extension_len], extension_len) != 0)
		end_program(data, WRONG_MAP_NAME, WRONG_MAP_NAME_MSG);
}

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

void	get_file_content(t_data *data, char *filename)
{
	int		fd;
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		end_program(data, OPENING_MAP_FAILED, FAILED_AT_OPENING_MAP_MSG);
	content = read_all(fd);
	close(fd);
	if (content == NULL)
		end_program(data, READING_MAP_FAILED, FAILED_AT_READING_MAP_MSG);
	content = skip_head_tail_empty_lines(content);
	if (content == NULL)
		end_program(data, EMPTY_MAP, EMPTY_MAP_MSG);
	if (check_empty_line(content) == false)
	{
		free(content);
		end_program(data, HAS_EMPTY_LINE, HAS_EMPTY_LINE_MSG);
	}
	data->map.array = ft_split(content, '\n');
	free(content);
	if (data->map.array == NULL)
		end_program(data, MALLOC_FAILED, FAILED_ON_MALLOC_MSG);
}

void	check_map(t_data *data, char *filename)
{
	data->map.array = NULL;
	check_filename(data, filename);
	get_file_content(data, filename);
	check_content(data);
}
