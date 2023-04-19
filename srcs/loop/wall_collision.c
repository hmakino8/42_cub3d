/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:54:47 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/19 18:56:25 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_pos	move(t_pos pos, double angle, double distance)
{
	t_pos	new_pos;

	new_pos.x = pos.x + distance * cos(deg_to_rad(angle));
	new_pos.y = pos.y + distance * -sin(deg_to_rad(angle));
	return (new_pos);
}

void	check_wall_collison(t_data *data, double dist, double angle)
{
	t_pos	pos;
	t_ray	move_ray;
	double	r_dist;

	pos.y = -P_SIZE;
	while (pos.y <= P_SIZE)
	{
		pos.x = -P_SIZE_HALF;
		while (pos.x <= P_SIZE_HALF)
		{
			move_ray.p_pos.x = data->ray.p_pos.x + pos.x;
			move_ray.p_pos.y = data->ray.p_pos.y + pos.y;
			move_ray.r_angle = angle;
			init_ray(&move_ray);
			ray_collision_detection(data, &move_ray);
			r_dist = (fabs((double)move_ray.p_pos.x - move_ray.r_pos.f_x)
				+ fabs((double)move_ray.p_pos.y - move_ray.r_pos.f_y));
			if (dist * 2.0 >= r_dist)
				return ;
			if (pos.y == -P_SIZE_HALF || pos.y == P_SIZE_HALF)
				pos.x++;
			else
				pos.x += P_SIZE;
		}
		pos.y++;
	}
	data->ray.p_pos = move(data->ray.p_pos, angle, P_MOVE);
}
