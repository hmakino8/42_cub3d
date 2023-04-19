/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_settings.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/19 18:39:54 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_SETTINGS_H
# define CUB3D_SETTINGS_H

# ifndef BONUS
#  define BONUS 1
# endif

# define EPSILON 1e-10
# define NO_COLOR 0x123456
# define RAY 0xFF0000
# define CENTER_RAY_COLOR 0xFFFF00
# define BUFFER_SIZE 1024
# define FOV 66.0
# define DICT_CHANGE 5.0
# define HEIGHT_MIN 3
# define WIDTH_MIN 3
# define WIDTH_MAX 256
# define HEIGHT_MAX 128
# define MAP_SCALE 524288
# define MINIMAP_TRANSPARENCY 30
# define P_MOVE 65536
# define C_SIZE 32
# define P_SIZE 10
# define P_SIZE_HALF 5

# define WIN_WIDTH 1024
# define WIN_HEIGHT 720

# define MINI_MAP_WIDTH_MAX 256
# define MINI_MAP_HEIGHT_MAX 256
# define MINI_MAP_BORDER 5

# define EMPTY '0'
# define WALL '1'
# define P_N 'N'
# define P_S 'S'
# define P_E 'E'
# define P_W 'W'
# define DOOR 'D'
# define CHECK 'X'

# define MAP_FILE_EXTENSION ".cub"

# define WALL_XPM_PATH "./xpm_files/wall.xpm"
# define EMPTY_XPM_PATH "./xpm_files/empty.xpm"
# define PLAYER_XPM_PATH "./xpm_files/player.xpm"
# define NONE_XPM_PATH "./xpm_files/none.xpm"

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

#endif
