# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:06:24 by pfrances          #+#    #+#              #
#    Updated: 2023/04/21 17:23:21 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

#################################MANDATORY#####################################
MANDATORY = mandatory
###############################################################################
###################################MAIN########################################
###############################################################################
SRCS_DIR = ./srcs/$(MANDATORY)
OBJS_DIR = ./objs/$(MANDATORY)
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
											init_ray.c					\
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
											raycast.c					\
											rays.c)
LOOP_OBJS = $(subst $(LOOP_SRCS_DIR), $(LOOP_OBJS_DIR), $(LOOP_SRCS:.c=.o))
SRCS += $(LOOP_SRCS)
OBJS += $(LOOP_OBJS)
###############################################################################
###################################TOOLS#######################################
###############################################################################
TOOLS_SRCS_DIR = $(SRCS_DIR)/tools
TOOLS_OBJS_DIR = $(OBJS_DIR)/tools
TOOLS_SRCS = $(addprefix $(TOOLS_SRCS_DIR)/,	images_tools.c			\
												maths_utils.c			\
												read_all.c)
TOOLS_OBJS = $(subst $(TOOLS_SRCS_DIR), $(TOOLS_OBJS_DIR), $(TOOLS_SRCS:.c=.o))
SRCS += $(TOOLS_SRCS)
OBJS += $(TOOLS_OBJS)
###############################################################################


###################################BONUS#######################################
BONUS = bonus
###############################################################################
###################################MAIN########################################
###############################################################################
B_SRCS_DIR = ./srcs/$(BONUS)
B_OBJS_DIR = ./objs/$(BONUS)
B_MAIN_SRCS = $(addprefix $(B_SRCS_DIR)/,		cub3D_bonus.c					\
												end_program_bonus.c)
B_MAIN_OBJS = $(subst $(B_SRCS_DIR), $(B_OBJS_DIR), $(B_MAIN_SRCS:.c=.o))
B_SRCS = $(B_MAIN_SRCS)
B_OBJS = $(B_MAIN_OBJS)
###############################################################################
###################################INIT########################################
###############################################################################
B_INIT_SRCS_DIR = $(B_SRCS_DIR)/init
B_INIT_OBJS_DIR = $(B_OBJS_DIR)/init
B_INIT_SRCS = $(addprefix $(B_INIT_SRCS_DIR)/,	check_wall_bonus.c				\
												check_map_bonus.c				\
												get_file_content_bonus.c		\
												get_map_content_bonus.c			\
												init_images_bonus.c				\
												init_map_bonus.c				\
												init_ray_bonus.c				\
												init_window_bonus.c				\
												init_bonus.c					\
												set_textures_colors_bonus.c		\
												set_rgb_bonus.c)
B_INIT_OBJS = $(subst $(B_INIT_SRCS_DIR), $(B_INIT_OBJS_DIR), $(B_INIT_SRCS:.c=.o))
B_SRCS += $(B_INIT_SRCS)
B_OBJS += $(B_INIT_OBJS)
###############################################################################
###################################LOOP########################################
###############################################################################
B_LOOP_SRCS_DIR = $(B_SRCS_DIR)/loop
B_LOOP_OBJS_DIR = $(B_OBJS_DIR)/loop
B_LOOP_SRCS = $(addprefix $(B_LOOP_SRCS_DIR)/,	deal_keys_bonus.c				\
												loop_bonus.c					\
												raycast_bonus.c					\
												rays_bonus.c					\
												render_image_bonus.c)
B_LOOP_OBJS = $(subst $(B_LOOP_SRCS_DIR), $(B_LOOP_OBJS_DIR), $(B_LOOP_SRCS:.c=.o))
B_SRCS += $(B_LOOP_SRCS)
B_OBJS += $(B_LOOP_OBJS)
###############################################################################
###################################TOOLS#######################################
###############################################################################
B_TOOLS_SRCS_DIR = $(B_SRCS_DIR)/tools
B_TOOLS_OBJS_DIR = $(B_OBJS_DIR)/tools
B_TOOLS_SRCS = $(addprefix $(B_TOOLS_SRCS_DIR)/,	gradation_bonus.c			\
													images_tools_bonus.c		\
													maths_utils_bonus.c			\
													read_all_bonus.c)
B_TOOLS_OBJS = $(subst $(B_TOOLS_SRCS_DIR), $(B_TOOLS_OBJS_DIR), $(B_TOOLS_SRCS:.c=.o))
B_SRCS += $(B_TOOLS_SRCS)
B_OBJS += $(B_TOOLS_OBJS)
###############################################################################

LIBS_DIR = ./libraries
LIBFT_DIR = $(LIBS_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a
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

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) $(MLX_LIBS) $(MATH_LIB) -o $(NAME)

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

$(MLX): $(MLX_DIR)/Makefile
	make -C $(MLX_DIR)

$(MLX_DIR)/Makefile:
	git clone $(MLX_REPO) $(MLX_DIR)

clean:
	rm -rf $(OBJS_DIR)
	make -C $(LIBFT_DIR) clean
	if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -rf $(MLX_DIR)

re: fclean all

bonus: $(B_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) $(B_OBJS) $(LIBFT) $(MLX_LIBS) $(MATH_LIB) -o $(NAME)

$(B_INIT_OBJS_DIR)/%.o: $(B_INIT_SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(B_INIT_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(B_LOOP_OBJS_DIR)/%.o: $(B_LOOP_SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(B_LOOP_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(B_TOOLS_OBJS_DIR)/%.o: $(B_TOOLS_SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(B_TOOLS_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

$(B_OBJS_DIR)/%.o: $(B_SRCS_DIR)/%.c $(MLX)
	@mkdir -p $(B_OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINE_VARS) -c $< -o $@

.PHONY: all clean fclean re bonus
