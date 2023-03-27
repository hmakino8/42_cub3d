/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:45:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 10:17:18 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_window_size(t_data *data)
{
	t_size	screen;

	mlx_get_screen_size(data->mlx_ptr, &screen.w, &screen.h);
	data->win_size.h = data->map.size.h * BPP;
	if (data->win_size.h > screen.h)
		end_program(data, MAP_TOO_HIGH, MAP_TOO_HIGH_MSG);
	data->win_size.w = data->map.size.w * BPP;
	if (data->win_size.w > screen.w)
		end_program(data, MAP_TOO_WIDE, MAP_TOO_WIDE_MSG);
}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		end_program(data, INIT_MLX_FAILED, FAILED_AT_INIT_MLX_MSG);
	check_window_size(data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_size.w,
			data->win_size.h, "cub3D");
	if (data->win_ptr == NULL)
		end_program(data, INIT_WINDOW_FAILED, FAILED_AT_INIT_WINDOW_MSG);
}
