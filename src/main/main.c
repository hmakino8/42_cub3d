/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2023/03/21 09:34:27 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = alloc_s_data();
	init_s_matrix(data->mx);
	check_argc(data, argc);
	get_matrix(data, argv[1]);
	init_s_camera(&data->cam, data->mx);
	init_s_mlx(data, data->mlx);
	rendering(data, data->mlx, data->mx);
	key_hook(data, data->mlx);
	mlx_loop(data->mlx->init);
	cub3d_exit(data, NULL);
}

//__attribute__((destructor)) static void destructor()
//{
//	system("leaks -q cub3D");
//}
