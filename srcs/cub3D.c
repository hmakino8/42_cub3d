/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:45:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/19 14:35:41 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define CUBE_SIZE 64
#define PLAYER_SIZE 10
#define PLAYER_MOVE 5
#define MAP_SIZE_WIDTH 8
#define MAP_SIZE_HEIGHT 8

float degToRad(int a) { return a * M_PI/ 180.0;}
int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

int map[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH] =
{
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};

int player_x = 300;
int player_y = 300;
float player_delta_x;
float player_delta_y;
float player_angle;

void	destroy_images(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->wall_img.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->empty_img.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->player_img.mlx_img);
}

int	end_program(t_data *data)
{
	destroy_images(data);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

void	player_moves(size_t x, size_t y)
{
	if (map[(y + PLAYER_MOVE) / CUBE_SIZE][(x + PLAYER_MOVE) / CUBE_SIZE] == 1)
		return ;
	player_x = x;
	player_y = y;
}

int	deal_keys(int key, t_data *data)
{
	if (key == XK_Escape)
		end_program(data);
	if (key == XK_w)
		player_moves(player_x, player_y - PLAYER_MOVE);
	if (key == XK_a)
		player_moves(player_x - PLAYER_MOVE, player_y);
	if (key == XK_s)
		player_moves(player_x, player_y + PLAYER_MOVE);
	if (key == XK_d)
		player_moves(player_x + PLAYER_MOVE, player_y);
	if (key == XK_Left || key == XK_Right)
	{
		if (key == XK_Left)
			player_angle += 5;
		else
			player_angle -= 5;
		player_angle = FixAng(player_angle);
		player_delta_x = cos(degToRad(player_angle));
		player_delta_y = -sin(degToRad(player_angle));
	}
	return (0);
}

bool	set_xpm_img(void *mlx_ptr, t_img *img, char *path)
{
	img->mlx_img = mlx_xpm_file_to_image(mlx_ptr, path,
			&img->width, &img->height);
	return (img->mlx_img != NULL);
}

void	images_init(t_data *data)
{
	if (set_xpm_img(data->mlx_ptr, &data->wall_img, WALL_XPM_PATH) == false)
		return ;
	if (set_xpm_img(data->mlx_ptr, &data->empty_img, EMPTY_XPM_PATH) == false)
		return ;
	if (set_xpm_img(data->mlx_ptr, &data->player_img, PLAYER_XPM_PATH) == false)
		return ;
}

void	drawPlayer(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->player_img.mlx_img, player_x, player_y);
	size_t	x = player_x;
	size_t	y = player_y;
	while (y < (size_t)player_y + 100)
	{
		x++;
		y++;
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0xFF1493);
	}
}

void	put_images(t_data *data, size_t x, size_t y)
{
	if (map[y][x] == 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->wall_img.mlx_img, x * CUBE_SIZE, y * CUBE_SIZE);
	else if (map[y][x] == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->empty_img.mlx_img, x * CUBE_SIZE, y * CUBE_SIZE);
}

int	render_map(t_data *data)
{
	size_t	x;
	size_t	y;

	if (data->win_ptr == NULL)
		return (1);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	y = 0;
	while (y < MAP_SIZE_HEIGHT)
	{
		x = 0;
		while (x < MAP_SIZE_WIDTH)
		{
			put_images(data, x, y);
			x++;
		}
		y++;
	}
	drawPlayer(data);
	return (0);
}

void	put_in_loop(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &render_map, data);
	mlx_hook(data->win_ptr, ClientMessage, StructureNotifyMask,
		&end_program, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &deal_keys, data);
	mlx_loop(data->mlx_ptr);
}

void	init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return ;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->window_width,
			data->window_height, "cub3D");
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		return ;
	}
}

int	main(void)
{
	t_data	data;

	data.window_height = MAP_SIZE_HEIGHT * CUBE_SIZE;
	data.window_width = MAP_SIZE_WIDTH * CUBE_SIZE;

	player_angle = 90;
	player_delta_x = cos(degToRad(player_angle));
	player_delta_y = -sin(degToRad(player_angle));

	init_window(&data);
	images_init(&data);
	put_in_loop(&data);
	return (0);
}