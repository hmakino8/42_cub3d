/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiroaki <hiroaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 12:36:49 by hiroaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include "cub3D_settings.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>

# include <printf.h>

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_pos
{
	size_t	x;
	size_t	y;
}	t_pos;

typedef struct s_delta_pos
{
	float	x;
	float	y;
}	t_delta_pos;

typedef struct s_player
{
	t_pos		pos;
	t_delta_pos	delta;
	float		angle;
}	t_player;

typedef struct s_map
{
	char	**array;
	size_t	height;
	size_t	width;
	bool	has_player;
}	t_map;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			cur_img;
	int			window_width;
	int			window_height;
	char		*file_content;
	t_img		wall_img;
	t_img		empty_img;
	t_img		player_img;
	t_map		map;
	t_player	player;
}	t_data;

/* cub3D.c */
void	print_error_messages(char *error_msg);

/* check_map.c */
void	check_map(t_data *data, char *filename);

/* check_map_content.c */
void	check_content(t_data *data);

/* init.c */
void	pgrm_init(t_data *data, char *filename);
void	init_window(t_data *data);
void	images_init(t_data *data);

/* loop.c */
void	put_in_loop(t_data *data);

/* render_image.c */
int		render_map(t_data *data);

/* end_program.c */
void	end_program(t_data *data, t_error error, char *error_msg);

/* maths_utils.c */
float	deg_to_rad(int a);
int		fix_ang(int a);

/* read_all.c */
char	*read_all(int fd);

#endif
