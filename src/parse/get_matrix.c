/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 02:08:05 by hiroaki           #+#    #+#             */
/*   Updated: 2023/03/21 09:31:58 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_height(t_data *data, t_matrix *mx, int *signal, int fd)
{
	mx->gnl = get_next_line(fd, signal);
	mx->line = ft_strtrim(mx->gnl, "\n ");
	free(mx->gnl);
	if (*signal == END_OF_FILE)
	{
		if (!mx->height)
			cub3d_exit(data, "Invalid map.");
		free(mx->line);
		mx->line = NULL;
		return ;
	}
	if (!mx->line)
		cub3d_exit(data, "Failed to read map.");
	mx->height++;
}

static void	get_width(t_data *data, t_matrix *mx)
{
	int	width;

	width = 0;
	free_all_element((void **)ft_split(mx->line, ' ', &width), width);
	free(mx->line);
	mx->line = NULL;
	check_width(data, mx, width);
}

static void	get_range(t_data *data, char *filename)
{
	int	fd;
	int	signal;

	init_fd(data, &fd, filename);
	while (1)
	{
		get_height(data, data->mx, &signal, fd);
		if (signal == END_OF_FILE)
			return ;
		get_width(data, data->mx);
	}
	close(fd);
}

static void	init_matrix(t_data *data, t_matrix *mx, char *filename)
{
	int	i;
	int	fd;
	int	damy;
	int	signal;

	init_fd(data, &fd, filename);
	i = -1;
	while (1)
	{
		mx->gnl = get_next_line(fd, &signal);
		mx->line = ft_strtrim(mx->gnl, "\n ");
		free(mx->gnl);
		if (signal == END_OF_FILE)
			return ;
		mx->elem = ft_split(mx->line, ' ', &damy);
		if (!mx->elem)
			cub3d_exit(data, "Failed to read map.");
		parse_line(data, mx, ++i);
		free(mx->line);
		mx->line = NULL;
	}
	close(fd);
}

void	get_matrix(t_data *data, char *filename)
{
	get_range(data, filename);
	alloc_arr(data, data->mx);
	init_matrix(data, data->mx, filename);
}
