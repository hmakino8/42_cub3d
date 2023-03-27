/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 10:18:07 by pfrances         ###   ########.fr       */
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

//void	draw_rays(t_data *data)
//{
//	t_pos
//}

void	draw_rays(t_data *data)
{
	t_pos	ray;
	t_pos	player_pxl;
	t_pos	side;
	t_pos	delta;

	delta = data->player.delta;
	delta.f_x *= BPP;
	delta.f_y *= BPP;

	player_pxl = data->player.pixel;

	if (delta.f_x > 0)
		side.f_x = BPP - (player_pxl.x % BPP);
	else
		side.f_x = -(player_pxl.x % BPP);
	if (delta.f_y > 0)
		side.f_y = BPP - (player_pxl.y % BPP);
	else
		side.f_y = -(player_pxl.y % BPP);

	if (fabs(side.f_x / delta.f_x) < fabs(side.f_y / delta.f_y))
	{
		//x de susumu
		ray.x = player_pxl.x + side.f_x;
		ray.y = player_pxl.y + fabs(side.f_x) * delta.f_y / BPP;

		side.f_x = BPP;
		side.f_y -= side.f_x * delta.f_y / BPP;
	}
	else if (fabs(side.f_x / delta.f_x) > fabs(side.f_y / delta.f_y))
	{
		//y de susumu
		ray.x = player_pxl.x + fabs(side.f_y) * delta.f_x / BPP;
		ray.y = player_pxl.y + side.f_y;

		side.f_x -= side.f_y * delta.f_x / BPP;
		side.f_y = BPP;
	}
	else {
		ray.x = player_pxl.x + side.f_x;
		ray.y = player_pxl.y + side.f_y;

		side.f_x = BPP;
		side.f_y = BPP;
	}

	ray.x -= PLAYER_SIZE / 2;
	ray.y -= PLAYER_SIZE / 2;
	printf("delta.f_x: %f  | delta.f_y: %f\n", delta.f_x, delta.f_y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.player.mlx_img, ray.x, ray.y);
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
		if (is_here_player(cur, data->player.pixel))
		{
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img.player.mlx_img,
				data->player.pixel.x, data->player.pixel.y);
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
	draw_rays(data);
	return (0);
}
