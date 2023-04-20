/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 05:36:19 by hiroaki           #+#    #+#             */
/*   Updated: 2023/04/20 15:17:37 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	brightness_control(int color, t_rgb_info *rgb)
{
	double	rt;

	rt = rgb->ratio * BRIGHTNESS;
	if (rt < 0.0)
		rt = 0.0;
	if (rt > 1.0)
		rt = 1.0;
	rgb->red = (color >> 16 & 0xFF) * rt;
	rgb->green = (color >> 8 & 0xFF) * rt;
	rgb->blue = (color & 0xFF) * rt;
	rgb->rgb = rgb->red << 16 | rgb->green << 8 | rgb->blue;
}

void	transparency_control(\
			int *color, t_data *data, t_pos map_pos, t_pos screen_pos)
{
	int			c1;
	int			c2;
	double		rt;
	t_rgb_info	rgb;

	c1 = get_pixel(&data->img.mini_map, map_pos);
	c2 = get_pixel(&data->img.screen, screen_pos);
	if (c1 == NO_COLOR)
		*color = c2;
	else
	{
		if (c1 == 0xFF0000)
			rt = 0.1;
		else
			rt = MINIMAP_TRANSPARENCY;
		rgb.red = (c1 >> 16 & 0xFF) * (1 - rt) + (c2 >> 16 & 0xFF) * rt;
		rgb.green = (c1 >> 8 & 0xFF) * (1 - rt) + (c2 >> 8 & 0xFF) * rt;
		rgb.blue = (c1 & 0xFF) * (1 - rt) + (c2 & 0xFF) * rt;
		*color = rgb.red << 16 | rgb.green << 8 | rgb.blue;
	}
}
