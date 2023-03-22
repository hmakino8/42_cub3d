/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:48:22 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 12:19:33 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
}

void	end_program(t_data *data, t_error error, char *error_msg)
{
	if (error != NONE)
		print_error_messages(error_msg);
	if (error >= NOT_BORDERED_BY_WALL)
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
