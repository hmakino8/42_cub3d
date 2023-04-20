/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:41:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/20 22:07:25 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_file_content(t_data *data, char *filename)
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
	data->save_door_pos = malloc(10000000 * sizeof(t_pos));
	data->save_door_color = malloc(10000000 * sizeof(int));
	data->ray.perp_w_dist_min = DBL_MAX;
	check_map(data, &data->map);
	init_window(data);
	images_init(data);
}
