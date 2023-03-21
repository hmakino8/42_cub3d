/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/21 16:06:46 by pfrances         ###   ########.fr       */
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
# define CUBE_SIZE 64
# define PLAYER_SIZE 10
# define PLAYER_MOVE 5

# define EMPTY '0'
# define WALL '1'
# define PLAYER_N 'N'
# define PLAYER_S 'S'
# define PLAYER_E 'E'
# define PLAYER_W 'W'
# define CHECKED_SPACE 'X'

# define MAP_FILE_EXTENSION ".cub"

# define WALL_XPM_PATH "./xpm_files/wall.xpm"
# define EMPTY_XPM_PATH "./xpm_files/empty.xpm"
# define PLAYER_XPM_PATH "./xpm_files/player.xpm"

# define ERROR_MSG "Error"
# define WRONG_NB_OF_ARGS_MSG "The programm take one argument: map path."
# define WRONG_MAP_NAME_MSG "The map name should be named like '[FILENAME].cub'"
# define FAILED_AT_OPENING_MAP_MSG "Failed at opening the map."
# define FAILED_AT_READING_MAP_MSG "Failed at reading the map."
# define EMPTY_MAP_MSG "The map is empty."
# define FAILED_AT_CLOSING_MAP_MSG "Failed at closing the map."
# define HAS_EMPTY_LINE_MSG "The map has empty line(s)."
# define FAILED_ON_MALLOC_MSG "Failed on memory allocation."
# define NOT_BORDERED_BY_WALL_MSG "The map has to be bordered by walls."
# define TO_MUCH_PLAYER_MSG "There are more than one player."
# define WRONG_SHAPE_MSG "The map shape is wrong. "
# define UNDEFINED_CHARACTER_MSG "There are undefined character(s)."
# define MAP_TOO_HIGH_MSG "The map is too high."
# define MAP_TOO_WIDE_MSG "The map is too wide."
# define HAS_NO_PLAYER_MSG "There no player."
# define FAILED_AT_INIT_MLX_MSG "Failed at init MLX."
# define FAILED_AT_INIT_WINDOW_MSG "Failed at init window."
# define FAILED_AT_INIT_IMGS_MSG "Failed at init images."
# define MLX_LOOP_ISSUE_MSG "Issue occured on MLX loop."

typedef enum e_error
{
	WRONG_NB_OF_ARGS,
	WRONG_MAP_NAME,
	OPENING_MAP_FAILED,
	READING_MAP_FAILED,
	EMPTY_MAP,
	FAILED_AT_CLOSING_MAP,
	HAS_EMPTY_LINE,
	MALLOC_FAILED,
	RESIZE_MALLOC_FAILED,
	NOT_BORDERED_BY_WALL,
	TOO_MUCH_PLAYER,
	UNDEFINED_CHARACTER,
	WRONG_SHAPE,
	HAS_NO_PLAYER,
	INIT_MLX_FAILED,
	MAP_TOO_HIGH,
	MAP_TOO_WIDE,
	INIT_WINDOW_FAILED,
	FAILED_AT_INIT_WALL_IMG,
	FAILED_AT_INIT_EMPTY_IMG,
	FAILED_AT_INIT_PLAYER_IMG,
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
	t_img		wall_img;
	t_img		empty_img;
	t_img		player_img;
	t_map		map;
	t_player	player;
}	t_data;

/*			cub3D.c					*/
void	print_error_messages(char *error_msg);

/*			get_file_content.c		*/
void	check_filename(t_data *data, char *str);
void	get_file_content(t_data *data, char *filename);

/*			check_map.c				*/
void	check_map(t_data *data, t_map *map);

/*			init_map.c	*/
void	init_map(t_data *data, t_map *map, char *filename);

/*			check_map_wall.c	*/
void	check_map_wall(t_data *data, t_map *map);

/*			init.c				*/
void	pgrm_init(t_data *data, char *filename);
void	init_window(t_data *data);
void	images_init(t_data *data);

/*			loop.c				*/
void	put_in_loop(t_data *data);

/*			render_image.c		*/
int		render_map(t_data *data);

/*			end_program.c		*/
void	end_program(t_data *data, t_error error, char *error_msg);

/*			maths_utils.c		*/
float	deg_to_rad(int a);
int		fix_ang(int a);

/*			read_all.c			*/
char	*read_all(int fd);

#endif