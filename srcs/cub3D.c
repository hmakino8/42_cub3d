/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 10:45:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/03 19:52:02 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		end_program(&data, WRONG_NB_OF_ARGS, WRONG_NB_OF_ARGS_MSG);
	pgrm_init(&data, argv[1]);
	put_in_loop(&data);
	return (0);
}
