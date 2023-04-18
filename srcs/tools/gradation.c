/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 05:36:19 by hiroaki           #+#    #+#             */
/*   Updated: 2023/04/19 00:19:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	brightness(int c, double rt)
{
	t_rgb_info	rgb;

	rgb.red = (c >> 16 & 0xFF) * rt;
	rgb.green = (c >> 8 & 0xFF) * rt;
	rgb.blue = (c & 0xFF) * rt;
	return (rgb.red << 16 | (rgb.green << 8) | rgb.blue);
}

int	add_brightness_to_texture(int color, t_data *data, t_ray *ray)
{
	double	ratio;

	ratio = ray->line_height / (double)data->win_size.h;
	if (ratio < 0.05)
		ratio = 0.05;
	else if (ratio > 1.0)
		ratio = 1.0;
	return (brightness(color, ratio));
}

int	add_brightness_to_rgb(int y, int color, t_data *data)
{
	double	ratio;

	ratio = (double)y / (double)data->win_size.h;
	if (ratio < 0.05)
		ratio = 0.05;
	else if (ratio > 1.0)
		ratio = 1.0;
	return (brightness(color, ratio));
}
