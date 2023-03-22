/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/22 14:02:20 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "ft_printf.h"
# include "libft.h"
# include "../libraries/minilibx/mlx.h"

# include <math.h>

# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>

# define BUFFER_SIZE 1024
# define HEIGHT_MIN 3
# define WITDH_MIN 3
# define BPP 64
# define PLAYER_SIZE 10
# define P_MOVE 5

# define EMPTY '0'
# define WALL '1'
# define P_N 'N'
# define P_S 'S'
# define P_E 'E'
# define P_W 'W'
# define CHECK 'X'

# define MAP_FILE_EXTENSION ".cub"

# define WALL_XPM_PATH "./xpm_files/wall.xpm"
# define EMPTY_XPM_PATH "./xpm_files/empty.xpm"
# define PLAYER_XPM_PATH "./xpm_files/player.xpm"

# define ERROR_MSG "Error"
# define FAILED_ON_MALLOC_MSG "Failed on memory allocation."
# define WRONG_NB_OF_ARGS_MSG "The programm take one argument: map path."
# define WRONG_MAP_NAME_MSG "The map name should be named like '[FILENAME].cub'"
# define FAILED_AT_OPENING_FILE_MSG "Failed at opening the map."
# define FAILED_AT_READING_FILE_MSG "Failed at reading the map."
# define FAILED_AT_CLOSING_FILE_MSG "Failed at closing the map."
# define HAS_DOUBLE_ENTRIE_MSG "A same element was declared twice."
# define INVALID_COLOR_MSG "A color set is invalid."
# define UNDEFINED_ENTRIE_MSG "There is a undefined entrie."
# define ELEMENT_MISSING_MSG "An element is missing."
# define EMPTY_MAP_MSG "The map is empty."
# define MAP_HAS_EMPTY_LINE_MSG "The map has empty line(s)."
# define WRONG_SHAPE_MSG "The map shape is wrong. "
# define TO_MUCH_PLAYER_MSG "There are more than one player."
# define MAP_UNDEF_CHAR_MSG "There are undefined character(s)."
# define HAS_NO_PLAYER_MSG "There no player."
# define NOT_BORDERED_BY_WALL_MSG "The map has to be bordered by walls."
# define FAILED_AT_INIT_MLX_MSG "Failed at init MLX."
# define MAP_TOO_HIGH_MSG "The map is too high."
# define MAP_TOO_WIDE_MSG "The map is too wide."
# define FAILED_AT_INIT_WINDOW_MSG "Failed at init window."
# define FAILED_AT_INIT_IMGS_MSG "Failed at init images."
# define MLX_LOOP_ISSUE_MSG "Issue occured on MLX loop."

typedef enum e_error
{
	WRONG_NB_OF_ARGS,
	WRONG_MAP_NAME,
	OPENING_FILE_FAILED,
	READING_FILE_FAILED,
	CLOSING_FILE_FAILED,
	HAS_DOUBLE_ENTRIE,
	INVALID_COLOR,
	IMG_PATH_MALLOC_FAILED,
	UNDEFINED_ENTRIE,
	ELEMENT_MISSING,
	GET_MAP_MALLOC_FAILED,
	EMPTY_MAP,
	MAP_HAS_EMPTY_LINE,
	MAP_SPLIT_MALLOC_FAILED,
	WRONG_SHAPE,
	RESIZE_MALLOC_FAILED,
	TOO_MUCH_PLAYER,
	MAP_UNDEF_CHAR,
	HAS_NO_PLAYER,
	NOT_BORDERED_BY_WALL,
	INIT_MLX_FAILED,
	MAP_TOO_HIGH,
	MAP_TOO_WIDE,
	INIT_WINDOW_FAILED,
	FAILED_AT_INIT_WALL_IMG,
	FAILED_AT_INIT_EMPTY_IMG,
	FAILED_AT_INIT_PLAYER_IMG,
	FAILED_AT_INIT_N_TEXT_IMG,
	FAILED_AT_INIT_S_TEXT_IMG,
	FAILED_AT_INIT_W_TEXT_IMG,
	FAILED_AT_INIT_E_TEXT_IMG,
	NONE
}	t_error;

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

typedef struct s_player
{
	int		x;
	int		y;
	float	delta_x;
	float	delta_y;
	float	angle;
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