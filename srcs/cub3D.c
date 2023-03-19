/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:45:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/19 17:59:43 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_error_messages(char *error_msg)
{
	ft_putendl_fd(ERROR_MSG, STDERR_FILENO);
	ft_putendl_fd(error_msg, STDERR_FILENO);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		end_program(&data, WRONG_NB_OF_ARGS, WRONG_NB_OF_ARGS_MSG);
	if (pgrm_init(&data, argv[1]) == false)
		return (2);
	data.window_height = data.map.height * CUBE_SIZE;
	data.window_width = data.map.width * CUBE_SIZE;
	data.player.delta_x = cos(deg_to_rad(data.player.angle));
	data.player.delta_y = -sin(deg_to_rad(data.player.angle));
	put_in_loop(&data);
	return (0);
}
