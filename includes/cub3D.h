/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/04/19 18:18:42 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include "cub3D_settings.h"

# include <math.h>
# include <float.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>

typedef enum e_slide		t_slide;
typedef enum e_error		t_error;
typedef struct s_size		t_size;
typedef struct s_map		t_map;
typedef struct s_pos		t_pos;
typedef struct s_fpos		t_fpos;
typedef struct s_img_info	t_img_info;
typedef struct s_img		t_img;
typedef struct s_rgb_info	t_rgb_info;
typedef struct s_rgb		t_rgb;
typedef struct s_ray		t_ray;
typedef struct s_data		t_data;

enum e_slide
{
	X_SLIDE,
	Y_SLIDE
};

enum e_error
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
	FAILED_AT_INIT_NONE_IMG,
	FAILED_AT_INIT_SCREEN_IMG,
	FAILED_AT_INIT_MINI_MAP_IMG,
	NONE
};

struct s_size
{
	int	w;
	int	h;
};

struct s_pos
{
	int	x;
	int	y;
};

struct s_fpos
{
	double	f_x;
	double	f_y;
};

struct s_img_info
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_len;
	char	*path;
	t_size	size;
};

struct s_img
{
	t_img_info	wall;
	t_img_info	empty;
	t_img_info	player;
	t_img_info	north_text;
	t_img_info	south_text;
	t_img_info	west_text;
	t_img_info	east_text;
	t_img_info	screen;
	t_img_info	mini_map;
	t_img_info	none;
};

struct s_rgb_info
{
	int		red;
	int		green;
	int		blue;
	int		rgb;
	double	gradation;
	bool	is_set;
};

struct s_rgb
{
	t_rgb_info	floor;
	t_rgb_info	ceiling;
};

struct s_ray
{
	t_pos	map;
	t_pos	p_pos;
	t_fpos	r_pos;
	t_pos	p_side;
	t_fpos	r_side;
	t_pos	r_dir;
	t_fpos	r_delta;
	double	r_angle;
	double	p_angle;
	t_pos	slide_cnt;
	t_slide	slide;
	bool	hit_wall;
	double	perp_w_dist;
	int		line_height;
	int		w_start;
	int		w_end;
	int		wall_hit_x;
	int		w_height;
};

struct s_map
{
	char	**array;
	bool	has_player;
	t_size	size;
	t_size	mini_map_size;
};

struct s_data
{
	int		cur_img;
	char	*file_content;
	void	*mlx_ptr;
	void	*win_ptr;
	t_size	win_size;
	t_img	img;
	t_rgb	color;
	t_map	map;
	t_ray	ray;
	int		old_mouse_x;
	int		w_colision_key;
};

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

/*								init_ray.c									*/
void	init_r_angle(t_ray *ray, double x, double w);
void	init_ray(t_ray *ray);

/*								init_images.c								*/
void	images_init(t_data *data);

/*								init_window.c								*/
void	init_window(t_data *data);

/*								init.c										*/
void	pgrm_init(t_data *data, char *filename);

/*								set_texture_and_color.c						*/
size_t	set_texture_and_color(t_data *data);

/*								set_rgb.c								*/
void	set_rgb(t_data *data, char *content, size_t *i, t_rgb_info *color);

/****************************************************************************/
/************************************LOOP************************************/
/****************************************************************************/

/*								deal_keys.c									*/
int		deal_keys(int key, void *ptr);
bool	check_new_pos(t_pos new_pos, char **map);
t_pos	move(t_pos pos, double angle, double distance);

/*								wall_collison.c								*/
void	check_wall_collison(t_data *data, double dist, double angle);

/*								deviation.c									*/
bool	deviation(t_ray *ray, t_pos pos, char **map, t_pos dist);

/*								loop.c										*/
void	put_in_loop(t_data *data);

/*								mini_map.c									*/
void	render_minimap(t_data *data);

/*								raycast.c									*/
void	do_raycasting(t_ray *ray, t_fpos *r_pos, t_fpos *r_side);
void	ray_collision_detection(t_data *data, t_ray *ray);
void	set_wall_size(t_data *data, t_ray *ray);
double	calculate_dist_to_wall(t_ray *ray);

/*								render_image.c								*/
void	put_mini_map(t_data *data);
int		render_map(t_data *data);

/****************************************************************************/
/************************************TOOLS***********************************/
/****************************************************************************/

/*								gradation.c									*/
int		brightness(int c, double rt);
int		add_brightness_to_texture(int color, t_data *data, t_ray *ray);
int		add_brightness_to_rgb(int y, int color, t_data *data);
int		transparency(int color1, int color2, double rt);

/*								images_tools.c								*/
int		get_pixel(t_img_info *img, t_pos img_pos);
void	put_pixel_to_img(t_img_info *img, t_pos pos, int color);
void	put_img_to_img(t_img_info *img1, t_img_info *img2, t_pos start);
void	put_text_to_screen(t_data *data, t_ray *ray, t_pos screen_pos);
void	draw_ray_lines(t_data *data, t_ray *ray, int color);

/*								maths_utils.c								*/
double	deg_to_rad(double a);
double	fix_ang(double a);
double	do_div(double num, double denum);

/*								read_all.c									*/
char	*read_all(int fd);

#endif
