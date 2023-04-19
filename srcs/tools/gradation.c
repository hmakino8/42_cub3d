/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 05:36:19 by hiroaki           #+#    #+#             */
/*   Updated: 2023/04/19 12:53:30 by pfrances         ###   ########.fr       */
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

	ratio = (ray->w_height / (double)data->win_size.h) * 2.5;
	if (ratio > 1.0)
		ratio = 1.0;
	return (brightness(color, ratio));
}

int	add_brightness_to_rgb(int y, int color, t_data *data)
{
	double	ratio;

	ratio = (1.0 - (double)y / (double)data->win_size.h);
	if (ratio < 0.5)
		ratio = 0.5;
	return (brightness(color, ratio));
}

int	transparency(int color1, int color2, double rt)
{
	t_rgb_info	rgb;

	if (color1 == NO_COLOR)
		return (color2);
	rgb.red = (color1 >> 16 & 0xFF) * (1 - rt) + (color2 >> 16 & 0xFF) * rt;
	rgb.green = (color1 >> 8 & 0xFF) * (1 - rt) + (color2 >> 8 & 0xFF) * rt;
	rgb.blue = (color1 & 0xFF) * (1 - rt) + (color2 & 0xFF) * rt;
	return (rgb.red << 16 | (rgb.green << 8) | rgb.blue);
}
