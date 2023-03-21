/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2023/03/21 09:21:48 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alloc_arr(t_data *d, t_matrix *mx)
{
	int	i;

	mx->alloccnt = 0;
	mx->coord = (int **)malloc(mx->height * sizeof(int *));
	mx->color = (int **)malloc(mx->height * sizeof(int *));
	if (!mx->coord || !mx->color)
		cub3d_exit(d, "Malloc failure");
	i = -1;
	while (++i < mx->height)
	{
		mx->coord[i] = (int *)malloc(mx->width * sizeof(int));
		mx->color[i] = (int *)malloc(mx->width * sizeof(int));
		if (!mx->coord[i] || !mx->color[i])
			cub3d_exit(d, "Malloc failure");
		mx->alloccnt++;
	}
}

t_data	*alloc_s_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data)
	{
		data->mx = (t_matrix *)malloc(sizeof(t_matrix));
		data->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	}
	if (!data || !data->mx || !data->mlx)
	{
		free_all_struct(data);
		ft_dprintf(2, "Malloc Failure\n");
		exit(EXIT_FAILURE);
	}
	return (data);
}
