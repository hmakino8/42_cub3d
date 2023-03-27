/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:50:38 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 14:22:58 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_ray(t_pos p_pos, t_ray *ray)
{
	ray->hit = false;
	ray->r_pos.x = p_pos.x - PLAYER_SIZE / 2;
	ray->r_pos.y = p_pos.y - PLAYER_SIZE / 2;
	ray->delta.f_x = cos(deg_to_rad(ray->angle)) * BPP;
	ray->delta.f_y = -sin(deg_to_rad(ray->angle)) * BPP;
	if (ray->delta.f_x >= 0)
		ray->dir.x = 1;
	else
		ray->dir.x = -1;
	if (ray->delta.f_y >= 0)
		ray->dir.y = 1;
	else
		ray->dir.y = -1;
	if (ray->delta.f_x > 0)
		ray->side.x = BPP - (p_pos.x % BPP);
	else
		ray->side.x = p_pos.x % BPP;
	if (ray->delta.f_y > 0)
		ray->side.y = BPP - (p_pos.y % BPP);
	else
		ray->side.y = p_pos.y % BPP;
}

void	check_wall(char **map, t_ray *ray, t_slide slide)
{
	t_pos	cell;

	cell.x = (ray->r_pos.x / BPP);
	cell.y = (ray->r_pos.y / BPP);
	if (slide == X_SLIDE || slide == XY_SLIDE)
		cell.x = (ray->r_pos.x / BPP) + (ray->dir.x > 0);
	if (slide == Y_SLIDE || slide == XY_SLIDE)
		cell.y = (ray->r_pos.y / BPP) + (ray->dir.y > 0);
	if (map[cell.y][cell.x] == WALL)
		ray->hit = true;
}

void	update_ray_pos(char **map, t_ray *ray, t_fpos side_div_delta)
{
	if (side_div_delta.f_x < side_div_delta.f_y)
	{
		ray->r_pos.x += ray->side.x * ray->dir.x;
		ray->r_pos.y += ray->side.x * ray->delta.f_y / BPP;
		ray->side.x = BPP;
		ray->side.y -= ray->side.x * fabs(ray->delta.f_y) / BPP;
		check_wall(map, ray, X_SLIDE);
	}
	else if (side_div_delta.f_x > side_div_delta.f_y)
	{
		ray->r_pos.x += ray->side.y * ray->delta.f_x / BPP;
		ray->r_pos.y += ray->side.y * ray->dir.y;
		ray->side.x -= ray->side.y * fabs(ray->delta.f_x) / BPP;
		ray->side.y = BPP;
		check_wall(map, ray, Y_SLIDE);
	}
	else
	{
		ray->r_pos.x += ray->side.x * ray->dir.x;
		ray->r_pos.y += ray->side.y * ray->dir.y;
		ray->side.x = BPP;
		ray->side.y = BPP;
		check_wall(map, ray, XY_SLIDE);
	}
}

void	draw_rays(t_data *data, t_player *player, t_ray *ray)
{
	t_fpos	side_div_delta;
	double	i;

	i = 0;
	while (i < data->win_size.w)
	{
		ray->angle = player->angle - FOV / 2.0 + i / data->win_size.w * FOV;
		init_ray(player->p_pos, ray);
		while (ray->hit == false)
		{
			side_div_delta.f_x = fabs(do_div(ray->side.x, ray->delta.f_x));
			side_div_delta.f_y = fabs(do_div(ray->side.y, ray->delta.f_y));
			update_ray_pos(data->map.array, ray, side_div_delta);
			// printf("delta.f_x: %f  | delta.f_y: %f\n",
			// 	player->delta.f_x, player->delta.f_y);
		}
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img.player.mlx_img, ray->r_pos.x, ray->r_pos.y);
		i++;
	}
}
