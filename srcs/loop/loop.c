/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:40:20 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/18 22:40:36 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cross_button_event(t_data *data)
{
	end_program(data, NONE, NULL);
	return (0);
}

int	mouse_hook(int mouse_x, int mouse_y, void *ptr)
{
	t_data	*data;

	(void)mouse_y;
	data = (t_data *)ptr;
	if (mouse_x == data->old_mouse_x)
		return (0);
	if (mouse_x > data->old_mouse_x)
		data->ray.p_angle -= 0.5;
	else
		data->ray.p_angle += 0.5;
	data->ray.p_angle = fix_ang(data->ray.p_angle);
	data->old_mouse_x = mouse_x;
	return (0);
}

void	put_in_loop(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render_map, data);
	mlx_hook(data->win_ptr, ClientMessage, StructureNotifyMask,
		&cross_button_event, data);
	if (BONUS)
		mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask,
			&mouse_hook, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &deal_keys, data);
	mlx_loop(data->mlx_ptr);
}
