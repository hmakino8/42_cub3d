/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:43:14 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 10:17:06 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	set_xpm_img(void *mlx_ptr, t_img_info *img, char *path)
{
	img->mlx_img = mlx_xpm_file_to_image(mlx_ptr, path,
			&img->size.w, &img->size.h);
	return (img->mlx_img != NULL);
}

void	images_init(t_data *data)
{
	if (!set_xpm_img(data->mlx_ptr, &data->img.wall, WALL_XPM_PATH))
		end_program(data, FAILED_AT_INIT_WALL_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (!set_xpm_img(data->mlx_ptr, &data->img.empty, EMPTY_XPM_PATH))
		end_program(data, FAILED_AT_INIT_EMPTY_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (!set_xpm_img(data->mlx_ptr, &data->img.player, PLAYER_XPM_PATH))
		end_program(data, FAILED_AT_INIT_PLAYER_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (!set_xpm_img(data->mlx_ptr, &data->no_text_img, data->no_text_img_path))
	// 	end_program(data, FAILED_AT_INIT_N_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (!set_xpm_img(data->mlx_ptr, &data->so_text_img, data->so_text_img_path))
	// 	end_program(data, FAILED_AT_INIT_S_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (!set_xpm_img(data->mlx_ptr, &data->we_text_img, data->we_text_img_path))
	// 	end_program(data, FAILED_AT_INIT_W_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
	// if (!set_xpm_img(data->mlx_ptr, &data->ea_text_img, data->ea_text_img_path))
	// 	end_program(data, FAILED_AT_INIT_E_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
}
