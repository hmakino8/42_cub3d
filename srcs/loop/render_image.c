/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:49:52 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/19 16:54:15 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	render_ray(t_data *data, t_ray *ray, int x)
{
	t_pos	pos;

	pos.y = 0;
	pos.x = x;
	while (pos.y < data->win_size.h)
	{
		if (pos.y > 0 && pos.y >= ray->w_start && pos.y <= ray->w_end)
			put_text_to_screen(data, ray, pos);
		else if (pos.y < ray->w_start)
			put_pixel_to_img(&data->img.screen, pos,
				add_brightness_to_rgb(pos.y, data->color.ceiling.rgb, data));
		else
			put_pixel_to_img(&data->img.screen, pos,
				add_brightness_to_rgb(pos.y, data->color.floor.rgb, data));
		pos.y++;
	}
}

void	draw_rays(t_data *data, t_ray *ray)
{
	int	x;
	int	w;

	x = 0;
	w = data->win_size.w;
	while (x < w)
	{
		init_r_angle(ray, (double)x, (double)w);
		init_ray(ray);
		ray_collision_detection(data, ray);
		set_wall_size(data, ray);
		render_ray(data, ray, x);
		if (BONUS)
			draw_ray_lines(data, ray, RAY);
		x++;
	}
}

int	render_map(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	if (BONUS)
		render_minimap(data);
	draw_rays(data, &data->ray);
	if (BONUS)
		put_mini_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->img.screen.img_ptr, 0, 0);
	return (0);
}
