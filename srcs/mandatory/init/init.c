/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:41:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 13:36:58 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parse_file_content(t_data *data, char *filename)
{
	size_t	map_start_index;

	check_filename(data, filename);
	get_file_content(data, filename);
	map_start_index = set_texture_and_color(data);
	get_map_content(data, map_start_index);
}

void	pgrm_init(t_data *data, char *filename)
{
	parse_file_content(data, filename);
	init_map(data, &data->map);
	check_map(data, &data->map);
	init_window(data);
	images_init(data);
}
