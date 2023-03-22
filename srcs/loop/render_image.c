/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 17:03:33 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// bool	is_here_player(t_pos cur, t_pos p_pos)
// {
// 	return (cur.x == p_pos.x / BPP && cur.y == p_pos.y / BPP);
// }

bool	is_within_the_view_point(t_pos p_pos, t_pos pos)
{
	return (pos.y < p_pos.y + 20 && pos.x < p_pos.x + 20);
}

bool	is_drawable(char **array, t_pos *ray)
{
	// if (pos.x / BPP > cur->x)
	// 	ray->x++;
	// if (pos.y / BPP > cur->y)
	// 	->y++;
	return (array[ray->y / BPP][ray->x / BPP] != WALL);
}

void	draw_view_point(t_data *data, t_pos pos, int i)
{
	void		*mlx_ptr;
	void		*win_ptr;

	mlx_ptr = data->mlx_ptr;
	win_ptr = data->win_ptr;
	mlx_pixel_put(mlx_ptr, win_ptr, pos.x - 1 + i, pos.y, VIEW_POINT);
	if (i < 2)
		draw_view_point(data, pos, i + 1);
}

void	draw_player(t_data *data, t_pos cur)
{
	t_pos		p_pos;
	t_pos		ray;
	t_delta_pos	delta;

	p_pos.x = data->player.pos_pxl.x;
	p_pos.y = data->player.pos_pxl.y;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->player_img.mlx_img, p_pos.x, p_pos.y);
	ray.x = p_pos.x + PLAYER_SIZE / 2;
	ray.y = p_pos.y + PLAYER_SIZE / 2;
	delta.x = 0;
	delta.y = 0;

	//int i = 0;
	//(void)cur;
	while (is_drawable(data->map.array, &ray))
	//while (i < 10)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray.x, ray.y, RAY);
		if (is_within_the_view_point(p_pos, ray))
			draw_view_point(data, ray, 0);
		printf("pos.x = %f\n", delta.x);
		printf("pos.y = %f\n", delta.y);
		delta.x += data->player.delta.x;
		delta.y += data->player.delta.y;
		ray.x += (int)delta.x;
		ray.y += (int)delta.y;
		// pos.x += tmp.x;
		// pos.y += tmp.y;
		//i++;
	}
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
	}
	draw_player(data, cur);
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
	return (0);
}
