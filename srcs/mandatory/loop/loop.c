/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:40:20 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 17:59:44 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	cross_button_event(t_data *data)
{
	end_program(data, NONE, NULL);
	return (0);
}

static int	render_map(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	draw_rays(data, &data->ray);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.screen.img_ptr, 0, 0);
	return (0);
}

void	put_in_loop(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render_map, data);
	mlx_hook(data->win_ptr, ClientMessage, StructureNotifyMask,
		&cross_button_event, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &deal_keys, data);
	mlx_loop(data->mlx_ptr);
}
