/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 01:01:29by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_player(t_data *data, t_pos cur, t_pos p_pos)
{
	return (cur.x == p_pos.x / CUBE_SIZE && \
			cur.y == p_pos.y / CUBE_SIZE);
}

bool	is_within_the_view_point(t_pos p_pos, t_pos pos)
{
	return (pos.y < p_pos.y + 20 && pos.x < p_pos.x + 20);
}

bool	is_drawable(char **array, t_pos *cur, t_pos pos)
{
	if (pos.x / CUBE_SIZE > cur->x)
		cur->x++;
	if (pos.y / CUBE_SIZE > cur->y)
		cur->y++;
	return (array[cur->y][cur->x] != WALL);
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

void	put_image_to_window(t_data *data, void *img, t_pos pos)
{
	void	*mlx;
	void	*win;

	mlx = data->mlx_ptr;
	win = data->win_ptr;
	mlx_put_image_to_window(mlx, win, img, pos.x, pos.y);
}

void	draw_player(t_data *data, t_pos cur)
{
	void		*img;
	t_pos		p_pos;
	t_pos		pos;
	t_pos		tmp;
	t_delta_pos	delta;

	p_pos.x = data->player.pos.x;
	p_pos.y = data->player.pos.y;
	img = data->player_img.mlx_img;
	put_image_to_window(data, img, p_pos);
	pos.x = p_pos.x + 5;
	pos.y = p_pos.y + 5;
	delta.x = 0;
	delta.y = 0;
	tmp.x = 0;
	tmp.y = 0;
	while (is_drawable(data->map.array, &cur, pos))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, pos.x, pos.y, RAY);
		if (is_within_the_view_point(p_pos, pos))
			draw_view_point(data, pos, 0);
		printf("pos.x = %zd\n", tmp.x);
		printf("pos.y = %zd\n", tmp.y);
		delta.x += data->player.delta.x;
		delta.y += data->player.delta.y;
		tmp.x = delta.x;
		tmp.y = delta.y;
		pos.x += tmp.x;
		pos.y += tmp.y;
	}
}

void	put_images(t_data *data, t_pos cur)
{
	char	**map;
	void	*img;
	t_pos	pos;

	map = data->map.array;
	pos.x = cur.x * CUBE_SIZE;
	pos.y = cur.y * CUBE_SIZE;
	if (map[cur.y][cur.x] == WALL)
		img = data->wall_img.mlx_img;
	if (map[cur.y][cur.x] == EMPTY)
		img = data->empty_img.mlx_img;
	put_image_to_window(data, img, pos);
	draw_player(data, cur);
}

int	render_map(t_data *data)
{
	t_pos	cur;

	if (data->win_ptr == NULL)
		return (1);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
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
