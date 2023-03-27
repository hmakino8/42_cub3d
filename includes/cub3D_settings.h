/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_settings.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/27 10:15:15 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_SETTINGS_H
# define CUB3D_SETTINGS_H

# define RAY 0x000000
# define VIEW_POINT 0xFF0000
# define BUFFER_SIZE 1024
# define FOV 66
# define DICT_CHANGE 5
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

#endif
