/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/26 14:21:58 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

///debug
# include <stdio.h>
///

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

typedef struct s_rgb_color
{
	int		red;
	int		green;
	int		blue;
	bool	is_set;
}	t_rgb;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_delta_pos
{
	float	x;
	float	y;
}	t_delta_pos;

typedef struct s_player
{
	t_pos		pos_pxl;
	t_delta_pos	delta;
	float		angle;
}	t_player;

typedef struct s_map
{
	char	**array;
	int		height;
	int		width;
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
	t_img		no_text_img;
	t_img		so_text_img;
	t_img		we_text_img;
	t_img		ea_text_img;
	t_img		floor_texture_img;
	t_img		ceiling_texture_img;
	char		*no_text_img_path;
	char		*so_text_img_path;
	char		*we_text_img_path;
	char		*ea_text_img_path;
	t_rgb		floor_color;
	t_rgb		ceiling_color;
	t_map		map;
	t_player	player;
}	t_data;

/****************************************************************************/
/************************************ROOT************************************/
/****************************************************************************/

/*								end_program.c								*/
void	end_program(t_data *data, t_error error, char *error_msg);
void	print_error_messages(char *error_msg);

/****************************************************************************/
/************************************INIT************************************/
/****************************************************************************/

/*								check_map.c									*/
void	check_map(t_data *data, t_map *map);

/*								check_wall.c								*/
void	check_map_wall(t_data *data, t_map *map);

/*								get_file_content.c							*/
void	check_filename(t_data *data, char *str);
void	get_file_content(t_data *data, char *filename);

/*								get_map_content.c							*/
void	get_map_content(t_data *data, size_t i);

/*								init_map.c									*/
void	init_map(t_data *data, t_map *map);

/*								init_images.c								*/
void	images_init(t_data *data);

/*								init_window.c								*/
void	init_window(t_data *data);

/*								init.c										*/
void	pgrm_init(t_data *data, char *filename);

/*								set_texture_and_color.c						*/
size_t	set_texture_and_color(t_data *data);

/*								set_rgb_color.c								*/
void	set_rgb_color(t_data *data, char *content, size_t *i, t_rgb *color);

/****************************************************************************/
/************************************LOOP************************************/
/****************************************************************************/

/*								deal_keys.c									*/
int		deal_keys(int key, t_data *data);

/*								loop.c										*/
void	put_in_loop(t_data *data);

/*								render_image.c								*/
int		render_map(t_data *data);

/****************************************************************************/
/************************************TOOLS***********************************/
/****************************************************************************/

/*								maths_utils.c								*/
float	deg_to_rad(int a);
int		fix_ang(int a);

/*								read_all.c									*/
char	*read_all(int fd);

#endif