/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:42:24 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 13:10:58 by pfrances         ###   ########.fr       */
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

void	get_file_content(t_data *data, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		end_program(data, OPENING_FILE_FAILED, FAILED_AT_OPENING_FILE_MSG);
	data->file_content = read_all(fd);
	if (data->file_content == NULL)
	{
		close(fd);
		end_program(data, READING_FILE_FAILED, FAILED_AT_READING_FILE_MSG);
	}
	if (close(fd) < 0)
	{
		free(data->file_content);
		end_program(data, CLOSING_FILE_FAILED, FAILED_AT_CLOSING_FILE_MSG);
	}
}
