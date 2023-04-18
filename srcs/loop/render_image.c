/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/18 17:12:45 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_here_player(t_pos cur, t_pos p_pos)
{
	if (cur.x == p_pos.x / MAP_SCALE && cur.y == p_pos.y / MAP_SCALE)
		return (true);
	else if (cur.x == (p_pos.x + PLAYER_SIZE) / MAP_SCALE && cur.y == p_pos.y / MAP_SCALE)
		return (true);
	else if (cur.x == p_pos.x / MAP_SCALE && cur.y == (p_pos.y + PLAYER_SIZE) / MAP_SCALE)
		return (true);
	else if (cur.x == (p_pos.x + PLAYER_SIZE) / MAP_SCALE
		&& cur.y == (p_pos.y + PLAYER_SIZE) / MAP_SCALE)
		return (true);
	return (false);
}

void	put_images(t_data *data, t_pos cur)
{
	char	**map;
	t_pos	img_pos;

	map = data->map.array;
	img_pos.x = cur.x * C_SIZE;
	img_pos.y = cur.y * C_SIZE;
	if (map[cur.y][cur.x] == WALL)
		put_img_to_img(&data->img.mini_map, &data->img.wall, img_pos);
	else if (map[cur.y][cur.x] == EMPTY)
	{
		put_img_to_img(&data->img.mini_map, &data->img.empty, img_pos);
		if (is_here_player(cur, data->ray.p_pos))
		{
			img_pos.x = data->ray.p_pos.x * C_SIZE / MAP_SCALE - PLAYER_SIZE / 2;
			img_pos.y = data->ray.p_pos.y * C_SIZE / MAP_SCALE - PLAYER_SIZE / 2;
			put_img_to_img(&data->img.mini_map, &data->img.player, img_pos);
		}
	}
	else
		put_img_to_img(&data->img.mini_map, &data->img.none, img_pos);
}

void	set_start_end_pos(t_map *map, t_pos p_pos, t_pos *start, t_pos *end)
{
	start->x = ((p_pos.x * C_SIZE) / MAP_SCALE - MINI_MAP_WIDTH_MAX / 2);
	start->y = ((p_pos.y * C_SIZE) / MAP_SCALE - MINI_MAP_HEIGHT_MAX / 2);
	end->x = ((p_pos.x * C_SIZE) / MAP_SCALE + MINI_MAP_WIDTH_MAX / 2);
	end->y = ((p_pos.y * C_SIZE) / MAP_SCALE + MINI_MAP_HEIGHT_MAX / 2);
	if (start->x < 0)
	{
		start->x = 0;
		end->x = start->x + MINI_MAP_WIDTH_MAX;
	}
	if (start->y < 0)
	{
		start->y = 0;
		end->y = start->y + MINI_MAP_HEIGHT_MAX;
	}
	if (end->x >= map->mini_map_size.w)
	{
		end->x = map->mini_map_size.w;
		start->x = (end->x - MINI_MAP_WIDTH_MAX) * (start->x > 0);
	}
	if (end->y >= map->mini_map_size.h)
	{
		end->y = map->mini_map_size.h;
		start->y = (end->y - MINI_MAP_HEIGHT_MAX) * (start->y > 0);
	}
}

void	put_mini_map(t_data *data)
{
	t_pos	map_pos;
	t_pos	screen_pos;
	t_pos	start;
	t_pos	end;
	int		color;

	set_start_end_pos(&data->map, data->ray.p_pos, &start, &end);
	map_pos.y = start.y;
	screen_pos.y = MINI_MAP_BORDER;
	while (map_pos.y < end.y)
	{
		map_pos.x = start.x;
		screen_pos.x = MINI_MAP_BORDER;
		while (map_pos.x < end.x)
		{
			color = get_pixel(&data->img.mini_map, map_pos);
			if (color != NO_COLOR)
				put_pixel_to_img(&data->img.screen, screen_pos, color);
			map_pos.x++;
			screen_pos.x++;
		}
		map_pos.y++;
		screen_pos.y++;
	}
}

int	render_map(t_data *data)
{
	t_pos	pos;

	if (data->win_ptr == NULL)
		return (1);
	pos.y = 0;
	while (pos.y < data->map.size.h)
	{
		pos.x = 0;
		while (pos.x < data->map.size.w)
		{
			put_images(data, pos);
			pos.x++;
		}
		pos.y++;
	}
	draw_rays(data, &data->ray);
	put_mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.screen.img_ptr, 0, 0);
	return (0);
}
