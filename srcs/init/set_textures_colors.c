/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures_colors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:42:14 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 14:01:38 by pfrances         ###   ########.fr       */
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
	data->no_text_img_path = NULL;
	data->so_text_img_path = NULL;
	data->we_text_img_path = NULL;
	data->ea_text_img_path = NULL;
	data->floor_color.red = -1;
	data->floor_color.green = -1;
	data->floor_color.blue = -1;
	data->floor_color.is_set = false;
	data->ceiling_color.red = -1;
	data->ceiling_color.green = -1;
	data->ceiling_color.blue = -1;
	data->ceiling_color.is_set = false;
}

bool	check_texture_and_color(t_data *data)
{
	if (data->no_text_img_path == NULL
		|| data->so_text_img_path == NULL
		|| data->we_text_img_path == NULL
		|| data->ea_text_img_path == NULL
		|| data->floor_color.is_set == false
		|| data->ceiling_color.is_set == false)
		return (false);
	return (true);
}

void	set_right_element(t_data *data, char *content, size_t *i)
{
	if (ft_strncmp(&content[*i], "NO", 2) == 0)
		set_img_path(data, content, i, &data->no_text_img_path);
	else if (ft_strncmp(&content[*i], "SO", 2) == 0)
		set_img_path(data, content, i, &data->so_text_img_path);
	else if (ft_strncmp(&content[*i], "WE", 2) == 0)
		set_img_path(data, content, i, &data->we_text_img_path);
	else if (ft_strncmp(&content[*i], "EA", 2) == 0)
		set_img_path(data, content, i, &data->ea_text_img_path);
	else if (ft_strncmp(&content[*i], "F", 1) == 0)
		set_rgb_color(data, content, i, &data->floor_color);
	else if (ft_strncmp(&content[*i], "C", 1) == 0)
		set_rgb_color(data, content, i, &data->ceiling_color);
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
