/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:45:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 22:17:49 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	check_window_size(t_data *data)
{
	if (data->map.size.h > HEIGHT_MAX)
		end_program(data, MAP_TOO_HIGH, MAP_TOO_HIGH_MSG);
	if (data->map.size.w > WITDH_MAX)
		end_program(data, MAP_TOO_WIDE, MAP_TOO_WIDE_MSG);
	data->win_size.w = WIN_WIDTH;
	data->win_size.h = WIN_HEIGHT;
	data->last_mouse_x = data->win_size.w / 2;
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
