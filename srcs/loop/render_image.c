/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 13:10:42 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_here_player(t_pos cur, t_pos p_pos)
{
	if (cur.x == p_pos.x / BPP && cur.y == p_pos.y / BPP)
		return (true);
	else if (cur.x == (p_pos.x + PLAYER_SIZE) / BPP && cur.y == p_pos.y / BPP)
		return (true);
	else if (cur.x == p_pos.x / BPP && cur.y == (p_pos.y + PLAYER_SIZE) / BPP)
		return (true);
	else if (cur.x == (p_pos.x + PLAYER_SIZE) / BPP
		&& cur.y == (p_pos.y + PLAYER_SIZE) / BPP)
		return (true);
	return (false);
}

void	put_images(t_data *data, t_pos cur)
{
	char	**map;
	t_pos	pos;

	map = data->map.array;
	pos.x = cur.x * BPP;
	pos.y = cur.y * BPP;
	if (map[cur.y][cur.x] == WALL)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.wall.mlx_img, pos.x, pos.y);
	}
	else if (map[cur.y][cur.x] == EMPTY)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.empty.mlx_img, pos.x, pos.y);
		if (is_here_player(cur, data->player.p_pos))
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img.player.mlx_img,
				data->player.p_pos.x, data->player.p_pos.y);
		}
	}
}

int	render_map(t_data *data)
{
	t_pos	cur;

	if (data->win_ptr == NULL)
		return (1);
	cur.y = 0;
	while (cur.y < data->map.size.h)
	{
		cur.x = 0;
		while (cur.x < data->map.size.w)
		{
			put_images(data, cur);
			cur.x++;
		}
		cur.y++;
	}
	draw_rays(data, &data->player, &data->ray);
	return (0);
}
