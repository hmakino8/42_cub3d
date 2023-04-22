/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:22:53 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/21 23:05:46 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_pixel(t_img_info *img, t_pos img_pos)
{
	char	*src;
	int		offset;

	offset = (img_pos.y * img->line_len + img_pos.x * (img->bpp / 8));
	src = img->addr + offset;
	return (*(int *)src);
}

void	put_pixel_to_img(t_img_info *img, t_pos pos, int color)
{
	char	*dst;
	int		offset;

	offset = (pos.y * img->line_len + pos.x * (img->bpp / 8));
	dst = img->addr + offset;
	*(int *)dst = color;
}

void	put_img_to_img(t_img_info *img1, t_img_info *img2, t_pos start)
{
	t_pos	img1_pos;
	t_pos	img2_pos;
	int		color;

	img2_pos.y = 0;
	while (img2_pos.y < img2->size.h)
	{
		img2_pos.x = 0;
		while (img2_pos.x < img2->size.w)
		{
			img1_pos.x = img2_pos.x + start.x;
			img1_pos.y = img2_pos.y + start.y;
			color = get_pixel(img2, img2_pos);
			put_pixel_to_img(img1, img1_pos, color);
			img2_pos.x++;
		}
		img2_pos.y++;
	}
}

void	put_text_to_screen(t_data *data, t_ray *ray, t_pos screen_pos)
{
	t_pos		img_pos;
	t_img_info	*img;

	img = NULL;
	if (ray->slide == X_SLIDE && ray->r_dir.x > 0)
		img = &data->img.east_text;
	else if (ray->slide == X_SLIDE && ray->r_dir.x < 0)
		img = &data->img.west_text;
	else if (ray->slide != X_SLIDE && ray->r_dir.y > 0)
		img = &data->img.south_text;
	else if (ray->slide != X_SLIDE && ray->r_dir.y < 0)
		img = &data->img.north_text;
	img_pos.y = lround((double)((screen_pos.y - ray->w_start
					+ (ray->w_height - ray->line_height) / 2) * img->size.h)
			/ ray->w_height);
	img_pos.x = lround(ray->wall_hit_x * img->size.w / MAP_SCALE);
	put_pixel_to_img(&data->img.screen, screen_pos, get_pixel(img, img_pos));
}
