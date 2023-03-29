/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/29 23:39:04 by pfrances         ###   ########.fr       */
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

void	put_images(t_data *data, t_pos cur, t_pos start)
{
	char	**map;
	t_pos	img_pos;

	map = data->map.array;
	img_pos.x = (cur.x - start.x) * C_SIZE + MINI_MAP_BORDER;
	img_pos.y = (cur.y - start.y) * C_SIZE + MINI_MAP_BORDER;
	if (map[cur.y][cur.x] == WALL)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.wall.mlx_img, img_pos.x, img_pos.y);
	}
	else if (map[cur.y][cur.x] == EMPTY)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.empty.mlx_img, img_pos.x, img_pos.y);
		if (is_here_player(cur, data->ray.p_pos))
		{
			img_pos.x = (data->ray.p_pos.x * C_SIZE / BPP)
				- PLAYER_SIZE / 2 - start.x * C_SIZE + MINI_MAP_BORDER;
			img_pos.y = (data->ray.p_pos.y * C_SIZE / BPP)
				- PLAYER_SIZE / 2 - start.y * C_SIZE + MINI_MAP_BORDER;
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
				data->img.player.mlx_img, img_pos.x, img_pos.y);
		}
	}
}

void	set_start_end_pos(t_map *map, t_pos p_pos, t_pos *start, t_pos *end)
{
	start->x = (p_pos.x * C_SIZE / BPP - map->mini_map_size.w / 2) / C_SIZE;
	start->y = (p_pos.y * C_SIZE / BPP - map->mini_map_size.h / 2) / C_SIZE;
	end->x = (p_pos.x * C_SIZE / BPP + map->mini_map_size.w / 2) / C_SIZE;
	end->y = (p_pos.y * C_SIZE / BPP + map->mini_map_size.h / 2) / C_SIZE;
	if (start->x < 0)
	{
		start->x = 0;
		end->x = start->x + map->mini_map_size.w / C_SIZE;
	}
	if (start->y < 0)
	{
		start->y = 0;
		end->y = start->y + map->mini_map_size.h / C_SIZE;
	}
	if (end->x >= map->size.w)
	{
		end->x = map->size.w;
		start->x = end->x - map->mini_map_size.w / C_SIZE;
	}
	if (end->y >= map->size.h)
	{
		end->y = map->size.h;
		start->y = end->y - map->mini_map_size.h / C_SIZE;
	}
}

void	draw_player_direction(t_data *data, t_ray *ray, t_pos start)
{
	t_pos	pos;
	t_pos	tmp;
	double	angle;
	int		i;
	int		j;

	pos.x = (ray->p_pos.x * C_SIZE / BPP) - start.x * C_SIZE + MINI_MAP_BORDER;
	pos.y = (ray->p_pos.y * C_SIZE / BPP) - start.y * C_SIZE + MINI_MAP_BORDER;
	i = 0;
	while (i < VUE_CONE_SIZE)
	{
		j = 0;
		while (j < VUE_CONE_SIZE)
		{
			angle = ray->p_angle + FOV / 2 - (FOV / VUE_CONE_SIZE) * j;
			tmp.x = move(pos, angle, i).x;
			tmp.y = move(pos, angle, i).y;
			mlx_pixel_put(data->mlx_ptr, data->win_ptr,
				tmp.x, tmp.y, VUE_CONE_COLOR);
			j++;
		}
		i++;
	}
}

int	render_map(t_data *data)
{
	t_pos	cur;
	t_pos	start;
	t_pos	end;

	if (data->win_ptr == NULL)
		return (1);
	set_start_end_pos(&data->map, data->ray.p_pos, &start, &end);
	cur.y = start.y;
	while (cur.y < end.y)
	{
		cur.x = start.x;
		while (cur.x < end.x)
		{
			put_images(data, cur, start);
			cur.x++;
		}
		cur.y++;
	}
	draw_player_direction(data, &data->ray, start);
	draw_rays(data, &data->ray);
	return (0);
}
