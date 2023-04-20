/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:42:14 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/20 22:15:47 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_img_path(t_data *data, char *content, size_t *i, char **path_to_set)
{
	size_t	path_len;

	path_len = 0;
	if (*path_to_set != NULL)
		end_program(data, HAS_DOUBLE_ENTRIE, HAS_DOUBLE_ENTRIE_MSG);
	(*i) += 2;
	while (ft_isspace(content[*i]))
		(*i)++;
	while (content[*i + path_len] != '\0'
		&& !ft_isspace(content[*i + path_len]))
		path_len++;
	*path_to_set = ft_strndup(&content[*i], path_len);
	(*i) += path_len;
	if (*path_to_set == NULL)
		end_program(data, IMG_PATH_MALLOC_FAILED, FAILED_ON_MALLOC_MSG);
}

void	set_default_texture_color(t_data *data)
{
	data->img.north_text.path = NULL;
	data->img.south_text.path = NULL;
	data->img.west_text.path = NULL;
	data->img.east_text.path = NULL;
	data->color.floor.red = -1;
	data->color.floor.green = -1;
	data->color.floor.blue = -1;
	data->color.floor.is_set = false;
	data->color.ceiling.red = -1;
	data->color.ceiling.green = -1;
	data->color.ceiling.blue = -1;
	data->color.ceiling.is_set = false;
}

bool	check_texture_and_color(t_data *data)
{
	if (data->img.north_text.path == NULL
		|| data->img.south_text.path == NULL
		|| data->img.west_text.path == NULL
		|| data->img.east_text.path == NULL
		|| data->color.floor.is_set == false
		|| data->color.ceiling.is_set == false)
		return (false);
	return (true);
}

void	set_right_element(t_data *data, char *content, size_t *i)
{
	if (ft_strncmp(&content[*i], "NO", 2) == 0)
		set_img_path(data, content, i, &data->img.north_text.path);
	else if (ft_strncmp(&content[*i], "SO", 2) == 0)
		set_img_path(data, content, i, &data->img.south_text.path);
	else if (ft_strncmp(&content[*i], "WE", 2) == 0)
		set_img_path(data, content, i, &data->img.west_text.path);
	else if (ft_strncmp(&content[*i], "EA", 2) == 0)
		set_img_path(data, content, i, &data->img.east_text.path);
	else if (ft_strncmp(&content[*i], "F", 1) == 0)
		set_rgb(data, content, i, &data->color.floor);
	else if (ft_strncmp(&content[*i], "C", 1) == 0)
		set_rgb(data, content, i, &data->color.ceiling);
	else
		end_program(data, UNDEFINED_ENTRIE, UNDEFINED_ENTRIE_MSG);
}

size_t	set_texture_and_color(t_data *data)
{
	size_t	i;
	char	*content;

	i = 0;
	set_default_texture_color(data);
	content = data->file_content;
	while (content[i] != '\0' && !check_texture_and_color(data))
	{
		while (ft_isspace(content[i]))
			i++;
		set_right_element(data, content, &i);
	}
	if (content[i] == '\0' || !check_texture_and_color(data))
		end_program(data, ELEMENT_MISSING, ELEMENT_MISSING_MSG);
	return (i);
}
