/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/28 15:42:45 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_pos	get_side(t_pos pos, t_fpos delta)
{
	if (delta.f_x > 0)
		pos.x = BPP - (pos.x % BPP);
	else
		pos.x = pos.x % BPP;
	if (delta.f_y > 0)
		pos.y = BPP - (pos.x % BPP);
	else
		pos.y = pos.x % BPP;
	return (pos);
}

void	fixe_side(t_ray *ray)
{
	if (ray->next_slide == X_SLIDE || ray->next_slide == XY_SLIDE)
	{
		while (ray->r_pos.x % BPP != 0)
		{
			if (ray->r_pos.x % BPP > BPP - ray->r_pos.x % BPP)
				ray->r_pos.x++;
			else
				ray->r_pos.x--;
		}
	}
	if (ray->next_slide == Y_SLIDE || ray->next_slide == XY_SLIDE)
	{
		while (ray->r_pos.y % BPP != 0)
		{
			if (ray->r_pos.y % BPP > BPP - ray->r_pos.y % BPP)
				ray->r_pos.y++;
			else
				ray->r_pos.y--;
		}
	}
}

void	init_ray(t_pos p_pos, t_ray *ray)
{
	ray->hit = false;
	ray->delta.f_x = cos(deg_to_rad(ray->r_angle)) * BPP;
	ray->delta.f_y = -sin(deg_to_rad(ray->r_angle)) * BPP;
	ray->r_pos.x = p_pos.x;
	ray->r_pos.y = p_pos.y;
	if (ray->delta.f_x > 0)
		ray->dir.x = 1;
	else if (ray->delta.f_x < 0)
		ray->dir.x = -1;
	if (ray->delta.f_y > 0)
		ray->dir.y = 1;
	else if (ray->delta.f_y < 0)
		ray->dir.y = -1;
	ray->p_side = get_side(ray->p_pos, ray->delta);
	ray->r_side = ray->p_side;
	ray->slide_count.x = 0;
	ray->slide_count.y = 0;
}

void	check_wall(char **map, t_ray *ray)
{
	t_pos	cell;

	cell.x = (ray->r_pos.x / BPP);
	cell.y = (ray->r_pos.y / BPP);
	if (ray->next_slide == X_SLIDE || ray->next_slide == XY_SLIDE)
		cell.x = (ray->r_pos.x / BPP) - (ray->dir.x < 0);
	if (ray->next_slide == Y_SLIDE || ray->next_slide == XY_SLIDE)
		cell.y = (ray->r_pos.y / BPP) - (ray->dir.y < 0);
	printf("cell.x: %d | cell.y: %d | slide: %d\n", cell.x, cell.y, ray->next_slide);
	printf("delta.x: %lf | delta.y: %lf\n", ray->delta.f_x, ray->delta.f_y);
	if (map[cell.y][cell.x] == WALL)
		ray->hit = true;
}

void	update_ray_pos(t_ray *ray)
{
	ray->r_pos = ray->p_pos;
	if (ray->next_slide == X_SLIDE)
	{
		ray->r_pos.x += (ray->p_side.x + ray->slide_count.x * BPP) * ray->dir.x;
		ray->r_pos.y += (double)(ray->p_side.x + ray->slide_count.x * BPP) * ray->delta.f_y / BPP;
		ray->slide_count.x++;
	}
	else if (ray->next_slide == Y_SLIDE)
	{
		ray->r_pos.x += (double)(ray->p_side.y + ray->slide_count.y * BPP) * ray->delta.f_x / BPP;
		ray->r_pos.y += (ray->p_side.y + ray->slide_count.y * BPP) * ray->dir.y;
		ray->slide_count.y++;
	}
	else
	{
		ray->r_pos.x += (ray->p_side.x + ray->slide_count.x * BPP) * ray->dir.x;
		ray->r_pos.y += (ray->p_side.y + ray->slide_count.y * BPP) * ray->dir.y;
		ray->slide_count.x++;
		ray->slide_count.y++;
	}
	ray->r_side = get_side(ray->r_pos, ray->delta);
	// fixe_side(ray);
}

void	set_next_slide(t_ray *ray)
{
	t_fpos	side_div_delta;
	double	epsilon;

	epsilon = 0.00001;
	side_div_delta.f_x = fabs(do_div(ray->r_side.x, ray->delta.f_x));
	side_div_delta.f_y = fabs(do_div(ray->r_side.y, ray->delta.f_y));
	if (fabs(side_div_delta.f_x - side_div_delta.f_y) < epsilon)
		ray->next_slide = XY_SLIDE;
	else if (side_div_delta.f_x < side_div_delta.f_y)
		ray->next_slide = X_SLIDE;
	else
		ray->next_slide = Y_SLIDE;
}

void	draw_rays(t_data *data, t_ray *ray)
{
	// double	i;

	// i = 0;
	// while (i < data->win_size.w)
	// {
		ray->r_angle = ray->p_angle;// - FOV / 2.0 + i / (double)data->win_size.w * FOV;
		init_ray(ray->p_pos, ray);
		printf("---------------------\n");
		while (ray->hit == false)
		{
			set_next_slide(ray);
			update_ray_pos(ray);
			check_wall(data->map.array, ray);
			// printf("delta.f_x: %lf | delta.f_y: %lf | slide: %d\n",
			// 	ray->delta.f_x, ray->delta.f_y, ray->next_slide);
			// printf("[%lf] ray.x: %d | ray.y: %d\n", i, ray->r_pos.x, ray->r_pos.y);
			// i++;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.player.mlx_img,
			ray->r_pos.x - PLAYER_SIZE / 2, ray->r_pos.y - PLAYER_SIZE / 2);
		}
		// mlx_pixel_put(data->mlx_ptr, data->win_ptr, ray->r_pos.x, ray->r_pos.y, VIEW_POINT);
	// 	i++;
	// }
}
