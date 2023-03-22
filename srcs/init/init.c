/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:41:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 16:41:01 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_parse(t_data *data)
{
	size_t	y;

	ft_printf("north: '%s'\nsouth: '%s'\nwest: '%s'\neast: '%s'\n\n",
		data->no_text_img_path, data->so_text_img_path,
		data->we_text_img_path, data->ea_text_img_path);
	ft_printf("f_red: '%d'\nf_green: '%d'\nf_blue: '%d'\nf_is_set : '%d'\n\n",
		data->floor_color.red, data->floor_color.green,
		data->floor_color.blue, data->floor_color.is_set);
	ft_printf("c_red: '%d'\nc_green: '%d'\nc_blue: '%d'\nc_is_set : '%d'\n\n",
		data->ceiling_color.red, data->ceiling_color.green,
		data->ceiling_color.blue, data->ceiling_color.is_set);
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
	check_map(data, &data->map);
	init_window(data);
	images_init(data);

	data->player.delta.x = cos(deg_to_rad(data->player.angle));
	data->player.delta.y = -sin(deg_to_rad(data->player.angle));
}
