# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:06:24 by pfrances          #+#    #+#              #
#    Updated: 2023/03/29 18:00:37 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS_DIR = srcs
OBJS_DIR = objs

###############################################################################
###################################MAIN########################################
###############################################################################
SRCS_DIR = ./srcs
OBJS_DIR = ./objs
MAIN_SRCS = $(addprefix $(SRCS_DIR)/,			cub3D.c					\
												end_program.c)
MAIN_OBJS = $(subst $(SRCS_DIR), $(OBJS_DIR), $(MAIN_SRCS:.c=.o))
SRCS = $(MAIN_SRCS)
OBJS = $(MAIN_OBJS)
###############################################################################
###################################INIT########################################
###############################################################################
INIT_SRCS_DIR = $(SRCS_DIR)/init
INIT_OBJS_DIR = $(OBJS_DIR)/init
INIT_SRCS = $(addprefix $(INIT_SRCS_DIR)/,	check_wall.c				\
											check_map.c					\
											get_file_content.c			\
											get_map_content.c			\
											init_images.c				\
											init_map.c					\
											init_window.c				\
											init.c						\
											set_textures_colors.c		\
											set_rgb.c)
INIT_OBJS = $(subst $(INIT_SRCS_DIR), $(INIT_OBJS_DIR), $(INIT_SRCS:.c=.o))
SRCS += $(INIT_SRCS)
OBJS += $(INIT_OBJS)
###############################################################################
###################################LOOP########################################
###############################################################################
LOOP_SRCS_DIR = $(SRCS_DIR)/loop
LOOP_OBJS_DIR = $(OBJS_DIR)/loop
LOOP_SRCS = $(addprefix $(LOOP_SRCS_DIR)/,	deal_keys.c					\
											loop.c						\
											rays.c						\
											rays_utils.c				\
											render_image.c)
LOOP_OBJS = $(subst $(LOOP_SRCS_DIR), $(LOOP_OBJS_DIR), $(LOOP_SRCS:.c=.o))
SRCS += $(LOOP_SRCS)
OBJS += $(LOOP_OBJS)
###############################################################################
###################################TOOLS#######################################
###############################################################################
TOOLS_SRCS_DIR = $(SRCS_DIR)/tools
TOOLS_OBJS_DIR = $(OBJS_DIR)/tools
TOOLS_SRCS = $(addprefix $(TOOLS_SRCS_DIR)/,	maths_utils.c			\
												read_all.c)
TOOLS_OBJS = $(subst $(TOOLS_SRCS_DIR), $(TOOLS_OBJS_DIR), $(TOOLS_SRCS:.c=.o))
SRCS += $(TOOLS_SRCS)
OBJS += $(TOOLS_OBJS)
###############################################################################

LIBS_DIR = ./libraries
LIBFT_DIR = $(LIBS_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = $(LIBS_DIR)/ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/ft_printf.a
MLX_DIR = $(LIBS_DIR)/minilibx
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MATH_LIB = -lm
INCLUDES = -I includes -I $(MLX_DIR)
DEFINE_VARS = -D $(ESC) -D $(W) -D $(A) -D $(S) -D $(D) -D $(FRAMERATE) -D $(ADJUST)

#--------------------------------------------------------------------------#

OS = $(shell uname -s)

ifeq ($(OS),Linux)
ESC = ESC=65307
W = W=119
A = A=97
S = S=115
D = D=100
FRAMERATE = FRAMERATE=1000
ADJUST = ADJUST=0
MLX = $(MLX_DIR)/libmlx.a
MLX_LIBS = -I $(MLX_DIR) -L $(MLX_DIR) -lmlx -lXext -lX11 $(MLX)
else
ESC = ESC=53
W = W=13
A = A=0
S = S=1
D = D=2
FRAMERATE = FRAMERATE=200
ADJUST = ADJUST=20
MLX = $(MLX_DIR)/libmlx_Darwin.a
INCLUDES += -I/usr/X11/include
MLX_LIBS = -L $(MLX_DIR) -L /usr/X11/include/../lib -lmlx_Darwin -lXext -lX11 -framework OpenGL -framework AppKit
endif

#--------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(FT_PRINTF) $(MLX_LIBS) $(MATH_LIB) -o $(NAME)

$(INIT_OBJS_DIR)/%.o: $(INIT_SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(INIT_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(LOOP_OBJS_DIR)/%.o: $(LOOP_SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(LOOP_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(TOOLS_OBJS_DIR)/%.o: $(TOOLS_SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(TOOLS_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

$(MLX): $(MLX_DIR)/Makefile
	make -C $(MLX_DIR)

$(MLX_DIR)/Makefile:
	git clone $(MLX_REPO) $(MLX_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean
	make -C $(FT_PRINTF_DIR) clean
	if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(FT_PRINTF)
	rm -rf $(MLX_DIR)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
