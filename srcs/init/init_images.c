/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:43:14 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 08:43:35 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	set_xpm_img(void *mlx_ptr, t_img *img, char *path)
{
	img->mlx_img = mlx_xpm_file_to_image(mlx_ptr, path,
			&img->width, &img->height);
	return (img->mlx_img != NULL);
}

void	images_init(t_data *data)
{
	if (set_xpm_img(data->mlx_ptr, &data->wall_img, WALL_XPM_PATH) == false)
		end_program(data, FAILED_AT_INIT_WALL_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (set_xpm_img(data->mlx_ptr, &data->empty_img, EMPTY_XPM_PATH) == false)
		end_program(data, FAILED_AT_INIT_EMPTY_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (set_xpm_img(data->mlx_ptr, &data->player_img, PLAYER_XPM_PATH) == false)
		end_program(data, FAILED_AT_INIT_PLAYER_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (set_xpm_img(data->mlx_ptr, &data->north_texture_img, data->north_texture_img_path) == false)
	// 	end_program(data, FAILED_AT_NORTH_TEXTURE_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (set_xpm_img(data->mlx_ptr, &data->south_texture_img, data->south_texture_img_path) == false)
	// 	end_program(data, FAILED_AT_SOUTH_TEXTURE_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (set_xpm_img(data->mlx_ptr, &data->west_texture_img, data->west_texture_img_path) == false)
	// 	end_program(data, FAILED_AT_WEST_TEXTURE_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (set_xpm_img(data->mlx_ptr, &data->east_texture_img, data->east_texture_img_path) == false)
	// 	end_program(data, FAILED_AT_EST_TEXTURE_IMG, FAILED_AT_INIT_IMGS_MSG);
}
