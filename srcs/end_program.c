/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:48:22 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 13:21:43 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_error_messages(char *error_msg)
{
	ft_putendl_fd(ERROR_MSG, STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

void	free_map(char **map_array)
{
	size_t	i;

	i = 0;
	while (map_array[i] != NULL)
	{
		free(map_array[i]);
		i++;
	}
	free(map_array);
}

void	destroy_images(t_data *data, t_error error)
{
	if (error >= FAILED_AT_INIT_WALL_IMG)
		mlx_destroy_image(data->mlx_ptr, data->wall_img.mlx_img);
	if (error >= FAILED_AT_INIT_EMPTY_IMG)
		mlx_destroy_image(data->mlx_ptr, data->empty_img.mlx_img);
	if (error >= FAILED_AT_INIT_PLAYER_IMG)
		mlx_destroy_image(data->mlx_ptr, data->player_img.mlx_img);
	// if (error >= FAILED_AT_NORTH_TEXTURE_IMG)
	// 	mlx_destroy_image(data->mlx_ptr, data->north_texture_img.mlx_img);
	// if (error >= FAILED_AT_SOUTH_TEXTURE_IMG)
	// 	mlx_destroy_image(data->mlx_ptr, data->south_texture_img.mlx_img);
	// if (error >= FAILED_AT_WEST_TEXTURE_IMG)
	// 	mlx_destroy_image(data->mlx_ptr, data->west_texture_img.mlx_img);
	// if (error >= FAILED_AT_EST_TEXTURE_IMG)
	// 	mlx_destroy_image(data->mlx_ptr, data->east_texture_img.mlx_img);
}

void	end_program(t_data *data, t_error error, char *error_msg)
{
	if (error != NONE)
		print_error_messages(error_msg);
	if (error >= HAS_DOUBLE_ENTRIE)
	{
		free(data->north_texture_img_path);
		free(data->south_texture_img_path);
		free(data->west_texture_img_path);
		free(data->east_texture_img_path);
		free(data->file_content);
	}
	if (error >= WRONG_SHAPE)
		free_map(data->map.array);
	if (error >= FAILED_AT_INIT_WALL_IMG)
	{
		destroy_images(data, error);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	}
	if (error > INIT_MLX_FAILED)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	exit(error > NONE);
}
