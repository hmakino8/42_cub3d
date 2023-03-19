/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:32:00 by pfrances          #+#    #+#             */
/*   Updated: 2023/03/19 12:11:49 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"

#include <math.h>

# include <X11/X.h>
# include <X11/keysym.h>
// # include <sys/types.h>
// # include <sys/stat.h>
// # include <fcntl.h>
// # include <stdbool.h>
# include <stdlib.h>

# define WALL_XPM_PATH "./xpm_files/wall.xpm"
# define EMPTY_XPM_PATH "./xpm_files/empty.xpm"
# define PLAYER_XPM_PATH "./xpm_files/player.xpm"

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
}	t_data;

#endif