/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:40:20 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/19 17:59:43 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	player_moves(t_data *data, size_t x, size_t y)
{
	if (data->map.array[(y + PLAYER_MOVE) / CUBE_SIZE][(x + PLAYER_MOVE) / CUBE_SIZE] == WALL)
		return ;
	data->player.x = x;
	data->player.y = y;
}

int	deal_keys(int key, t_data *data)
{
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	if (key == XK_w)
		player_moves(data, data->player.x, data->player.y - PLAYER_MOVE);
	if (key == XK_a)
		player_moves(data, data->player.x - PLAYER_MOVE, data->player.y);
	if (key == XK_s)
		player_moves(data, data->player.x, data->player.y + PLAYER_MOVE);
	if (key == XK_d)
		player_moves(data, data->player.x + PLAYER_MOVE, data->player.y);
	if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			data->player.angle += 5;
		else
			data->player.angle -= 5;
		data->player.angle = fix_ang(data->player.angle);
		data->player.delta_x = cos(deg_to_rad(data->player.angle));
		data->player.delta_y = -sin(deg_to_rad(data->player.angle));
	}
	return (0);
}

int	cross_button_event(t_data *data)
{
	end_program(data, NONE, NULL);
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
