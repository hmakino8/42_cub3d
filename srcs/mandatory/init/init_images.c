/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:43:14 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 17:07:12 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	set_xpm_img(void *mlx_ptr, t_img_info *img)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, img->path,
			&img->size.w, &img->size.h);
	if (img->img_ptr != NULL)
		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
				&img->line_len, &img->endian);
	return (img->img_ptr != NULL);
}

static bool	new_img(void *mlx_ptr, t_img_info *img, t_size size)
{
	img->img_ptr = mlx_new_image(mlx_ptr, size.w, size.h);
	if (img->img_ptr != NULL)
		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
				&img->line_len, &img->endian);
	return (img->img_ptr != NULL);
}

void	images_init(t_data *data)
{
	if (!set_xpm_img(data->mlx_ptr, &data->img.north_text))
		end_program(data, FAILED_AT_INIT_N_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (!set_xpm_img(data->mlx_ptr, &data->img.south_text))
		end_program(data, FAILED_AT_INIT_S_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (!set_xpm_img(data->mlx_ptr, &data->img.west_text))
		end_program(data, FAILED_AT_INIT_W_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (!set_xpm_img(data->mlx_ptr, &data->img.east_text))
		end_program(data, FAILED_AT_INIT_E_TEXT_IMG, FAILED_AT_INIT_IMGS_MSG);
	if (!new_img(data->mlx_ptr, &data->img.screen, data->win_size))
		end_program(data, FAILED_AT_INIT_SCREEN_IMG, FAILED_AT_INIT_IMGS_MSG);
}
