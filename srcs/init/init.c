/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:41:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 09:39:45 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_parse(t_data *data)
{
	size_t	y;

	ft_printf("north: '%s'\nsouth: '%s'\nwest: '%s'\neast: '%s'\n\n",
		data->north_texture_img_path, data->south_texture_img_path, data->west_texture_img_path, data->east_texture_img_path);
	ft_printf("floor_red: '%d'\nfloor_green: '%d'\nfloor_blue: '%d'\nfloor_is_set : '%d'\n\n",
		data->floor_color.red, data->floor_color.green, data->floor_color.blue, data->floor_color.is_set);
	ft_printf("ceiling_red: '%d'\nceiling_green: '%d'\nceiling_blue: '%d'\nceiling_is_set : '%d'\n\n",
		data->ceiling_color.red, data->ceiling_color.green, data->ceiling_color.blue, data->ceiling_color.is_set);
	y = 0;
	while (data->map.array[y] != NULL)
	{
		ft_putendl_fd(data->map.array[y], STDOUT_FILENO);
		y++;
	}
}

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
	//check_parse(data);
	init_map(data, &data->map);
	init_window(data);
	images_init(data);
}
