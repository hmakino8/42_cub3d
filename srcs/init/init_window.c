/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:45:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 13:25:32 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_window_size(t_data *data)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(data->mlx_ptr, &screen_width, &screen_height);
	data->window_height = data->map.height * BPP;
	if (data->window_height > screen_height)
		end_program(data, MAP_TOO_HIGH, MAP_TOO_HIGH_MSG);
	data->window_width = data->map.width * BPP;
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
