/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deviation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:21:40 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/19 15:42:50 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	count_angle_change(t_ray *ray, t_pos pos, char **map, int delta)
{
	double	angle;
	size_t	i;
	t_pos	new_pos;

	i = 0;
	angle = ray->p_angle;
	new_pos = pos;
	while (check_new_pos(new_pos, map) == false)
	{
		new_pos = move(ray->p_pos, angle, P_MOVE);
		angle = fix_ang(angle + delta);
		i++;
	}
	return (i);
}

bool	deviation(t_ray *ray, t_pos pos, char **map, t_pos dist)
{
	size_t	right_change;
	size_t	left_change;

	return (false);
	pos.x += dist.x;
	pos.y += dist.y;
	right_change = count_angle_change(ray, pos, map, 1.0);
	pos.x += dist.x;
	pos.y += dist.y;
	left_change = count_angle_change(ray, pos, map, -1.0);
	if (left_change > 45 && right_change > 45)
		return (false);
	if (left_change < right_change)
		ray->p_angle = fix_ang(ray->p_angle - 1.0);
	else
		ray->p_angle = fix_ang(ray->p_angle + 1.0);
	return (true);
}
