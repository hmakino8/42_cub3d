/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:40:20 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/19 15:45:09 by pfrances         ###   ########.fr       */
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
	double	mouse_f_x;

	(void)mouse_y;
	mouse_f_x = (double)mouse_x;
	data = (t_data *)ptr;
	if (mouse_x == data->old_mouse_x)
		return (0);
	if (mouse_x > data->old_mouse_x)
		data->ray.p_angle -= 0.5 * (mouse_f_x
				/ ((double)data->win_size.w / 2.0));
	else if (mouse_x < data->old_mouse_x)
		data->ray.p_angle += 0.5 * ((double)data->win_size.w - mouse_f_x)
			/ ((double)data->win_size.w / 2.0);
	data->ray.p_angle = fix_ang(data->ray.p_angle);
	data->old_mouse_x = mouse_x;
	return (0);
}

int	wait_release(int key, t_data *data)
{
	if (key == data->w_colision_key)
	{
		printf("release key: %d\n", key);
		data->w_colision_key = -1;
	}
	return (0);
}

void	put_in_loop(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render_map, data);
	mlx_hook(data->win_ptr, ClientMessage, StructureNotifyMask,
		&cross_button_event, data);
	if (false)
		mlx_hook(data->win_ptr, MotionNotify, PointerMotionMask,
			&mouse_hook, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &wait_release, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &deal_keys, data);
	mlx_loop(data->mlx_ptr);
}
