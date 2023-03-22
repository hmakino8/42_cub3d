/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 13:25:32 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_player(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->player_img.mlx_img, data->player.x, data->player.y);
	// size_t	x = data->player.player_x;
	// size_t	y = data->player.player_y;
	// while (y < (size_t)data->player.player_y + 100)
	// {
	// 	x++;
	// 	y++;
	// 	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF1493);
	// }
}

void	put_images(t_data *data, size_t x, size_t y)
{
	if (data->map.array[y][x] == WALL)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->wall_img.mlx_img, x * BPP, y * BPP);
	else if (data->map.array[y][x] == EMPTY)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->empty_img.mlx_img, x * BPP, y * BPP);
}

int	render_map(t_data *data)
{
	size_t	x;
	size_t	y;

	if (data->win_ptr == NULL)
		return (1);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			put_images(data, x, y);
			x++;
		}
		y++;
	}
	draw_player(data);
	return (0);
}
