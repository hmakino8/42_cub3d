/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:40:20 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 12:07:33 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_move_key(int key)
{
	return (key == XK_w || key == XK_a || key == XK_s || key == XK_d);
}

bool	is_directory_key(int key)
{
	return  (key == XK_Left || key == XK_Right);
}

void	player_moves(int key, t_pos *p_pos, t_data *data)
{
	int		adj;
	t_pos	new;
	t_pos	tmp;

	new = *p_pos;
	adj = PLAYER_SIZE / 2;
	if (key == XK_w)
	{
		new.y -= PLAYER_MOVE;
		adj *= -1;
	}
	if (key == XK_a)
	{
		new.x -= PLAYER_MOVE;
		adj *= -1;
	}
	if (key == XK_s)
		new.y += PLAYER_MOVE;
	if (key == XK_d)
		new.x += PLAYER_MOVE;
	tmp.y = (new.y + PLAYER_MOVE + adj) / CUBE_SIZE;
	tmp.x = (new.x + PLAYER_MOVE + adj) / CUBE_SIZE;
	if (data->map.array[tmp.y][tmp.x] == WALL)
		return ;
	*p_pos = new;
}

int	deal_keys(int key, t_data *data)
{
	t_pos		*p_pos;
	t_delta_pos	*delta;

	p_pos = &data->player.pos;
	delta = &data->player.delta;
	if (key == XK_Escape)
		end_program(data, NONE, NULL);
	if (is_move_key(key))
		player_moves(key, p_pos, data);
	if (is_directory_key(key))
	{
		if (key == XK_Left)
			data->player.angle += 5;
		else
			data->player.angle -= 5;
		data->player.angle = fix_ang(data->player.angle);
		data->player.delta.x = cos(deg_to_rad(data->player.angle));
		data->player.delta.y = -sin(deg_to_rad(data->player.angle));
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
	mlx_hook(data->win_ptr, EVENT_1, MASK_1, &cross_button_event, data);
	mlx_hook(data->win_ptr, EVENT_2, MASK_2, &deal_keys, data);
	mlx_loop(data->mlx_ptr);
}
