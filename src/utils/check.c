/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2023/03/21 09:32:32 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_argc(t_data *data, int argc)
{
	if (argc != 2)
		cub3d_exit(data, "Invalid argument.");
}

void	check_width(t_data *data, t_matrix *mx, int width)
{
	if (!mx->width)
		mx->width = width;
	else if (mx->width != width)
		cub3d_exit(data, "Invalid width in map.");
}

int	check_z_axis(t_data *data, int z)
{
	if ((z > 0 && data->cam.zoom * data->cam.z_div <= INT_MAX / z) || \
		(z != 0 && z < -1 && data->cam.zoom * data->cam.z_div <= INT_MIN / z))
		return (z * data->cam.zoom * data->cam.z_div);
	return (z);
}

void	check_delta(t_data *data, t_pos delta)
{
	if (delta.x < 0 || delta.y < 0)
		stop_rendering(data, "Depth value too large to draw correctly.");
}

void	check_error(t_data *data, int error)
{
	if (error > INT_MAX / 2 || error < INT_MIN / 2)
		stop_rendering(data, "Depth value too large to draw correctly.");
}
