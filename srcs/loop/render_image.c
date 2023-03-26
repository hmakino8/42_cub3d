/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/26 14:22:51 by pfrances         ###   ########.fr       */
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
}

void	draw_rays(t_data *data)
{
	t_pos		ray;
	t_pos		player_pxl;
	t_delta_pos	side;
	t_delta_pos	delta;

	delta = data->player.delta;
	delta.x *= BPP;
	delta.y *= BPP;

	player_pxl = data->player.pos_pxl;

	if (delta.x > 0)
		side.x = BPP - (player_pxl.x % BPP);
	else
		side.x = -(player_pxl.x % BPP);
	if (delta.y > 0)
		side.y = BPP - (player_pxl.y % BPP);
	else
		side.y = -(player_pxl.y % BPP);

	if (fabs(side.x / delta.x) < fabs(side.y / delta.y))
	{
		//x de susumu
		ray.x = player_pxl.x + side.x;
		ray.y = player_pxl.y + fabs(side.x) * delta.y / BPP;

		side.x = BPP;
		side.y -= side.x * delta.y / BPP;
	}
	else if (fabs(side.x / delta.x) > fabs(side.y / delta.y))
	{
		//y de susumu
		ray.x = player_pxl.x + fabs(side.y) * delta.x / BPP;
		ray.y = player_pxl.y + side.y;

		side.x -= side.y * delta.x / BPP;
		side.y = BPP;
	}
	else {
		ray.x = player_pxl.x + side.x;
		ray.y = player_pxl.y + side.y;

		side.x = BPP;
		side.y = BPP;
	}

	ray.x -= PLAYER_SIZE / 2;
	ray.y -= PLAYER_SIZE / 2;
	printf("delta.x: %f  | delta.y: %f\n", delta.x, delta.y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->player_img.mlx_img, ray.x, ray.y);
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
			data->wall_img.mlx_img, pos.x, pos.y);
	}
	else if (map[cur.y][cur.x] == EMPTY)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->empty_img.mlx_img, pos.x, pos.y);
		if (is_here_player(cur, data->player.pos_pxl))
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->player_img.mlx_img,
				data->player.pos_pxl.x, data->player.pos_pxl.y);
		}
	}
}

int	render_map(t_data *data)
{
	t_pos	cur;

	if (data->win_ptr == NULL)
		return (1);
	cur.y = 0;
	while (cur.y < data->map.height)
	{
		cur.x = 0;
		while (cur.x < data->map.width)
		{
			put_images(data, cur);
			cur.x++;
		}
		cur.y++;
	}
	draw_rays(data);
	return (0);
}
