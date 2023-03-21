/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:41:05 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/21 16:04:08 by pfrances         ###   ########.fr       */
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
		return ;
	if (set_xpm_img(data->mlx_ptr, &data->empty_img, EMPTY_XPM_PATH) == false)
		return ;
	if (set_xpm_img(data->mlx_ptr, &data->player_img, PLAYER_XPM_PATH) == false)
		return ;
}

void	check_window_size(t_data *data)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	data->window_height = data->map.height * CUBE_SIZE;
	if (data->window_height > screen_height)
		end_program(data, MAP_TOO_HIGH, MAP_TOO_HIGH_MSG);
	data->window_width = data->map.width * CUBE_SIZE;
	if (data->window_width > screen_width)
		end_program(data, MAP_TOO_WIDE, MAP_TOO_WIDE_MSG);
}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		end_program(data, INIT_MLX_FAILED, FAILED_AT_INIT_MLX_MSG);
	check_window_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window_width,
			data->window_height, "cub3D");
	if (data->win_ptr == NULL)
		end_program(data, INIT_WINDOW_FAILED, FAILED_AT_INIT_WINDOW_MSG);
}

void	pgrm_init(t_data *data, char *filename)
{
	init_map(data, &data->map, filename);
	init_window(data);
	images_init(data);
}
