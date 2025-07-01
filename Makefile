# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mg <mg@student.42.fr>                      +#+  +:+       +#+         #
#                                                +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 14:54:30 by maximemarti       #+#    #+#              #
#    Updated: 2025/06/24 09:59:45 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME        = cube3d

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

SRCDIR      = src
OBJDIR      = obj
BONUS_SRCDIR = src_bonus
INCDIR      = includes
LIBFTDIR    = libft

MANDATORY_SRC_FILES = main.c \
				events/e_window.c \
				movement/m_move_player.c \
				movement/m_rotate_player.c \
				init/i_game.c \
				init/i_textures.c \
				parsing/p_check_texture.c \
				parsing/p_color.c \
				parsing/p_file.c \
				parsing/p_map_ok_u.c \
				parsing/p_map.c \
				parsing/p_texture.c \
				parsing/p_valid_map.c \
				raycasting/r_cast.c \
				render/r_background.c \
				render/r_wall.c \
				render/r_textures.c \
				render/r_loop.c \
				utils/u_cleanup.c \
				utils/u_dir_player.c \
				utils/u_move_player.c \
				print.c

SRCS        = $(addprefix $(SRCDIR)/, $(MANDATORY_SRC_FILES))
OBJS        = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJ_DIRS    = $(sort $(dir $(OBJS)))

BONUS_SRCS = \
	src_bonus/main.c \
	src_bonus/movement/m_move_player.c \
	src_bonus/render/r_loop.c \
	src_bonus/render/r_minimap.c \
	src_bonus/utils/u_map_size.c \
	src_bonus/utils/u_minimap.c \
	src_bonus/events/e_window.c \
	src_bonus/init/i_game.c \
	src_bonus/init/i_textures.c \
	src_bonus/parsing/p_check_texture.c \
	src_bonus/parsing/p_color.c \
	src_bonus/parsing/p_file.c \
	src_bonus/parsing/p_map_ok_u.c \
	src_bonus/parsing/p_map.c \
	src_bonus/parsing/p_texture.c \
	src_bonus/parsing/p_valid_map.c \
	src_bonus/raycasting/r_cast.c \
	src_bonus/render/r_background.c \
	src_bonus/render/r_wall.c \
	src_bonus/render/r_textures.c \
	src_bonus/utils/u_cleanup.c \
	src_bonus/utils/u_dir_player.c \
	src_bonus/movement/m_rotate_player.c \
	src_bonus/utils/u_move_player.c \

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

LIBFT       = $(LIBFTDIR)/libft.a

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
MLX_DIR = mlx_linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
MLX_INC = -I$(MLX_DIR)
else
MLX_DIR = mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
MLX_INC = -I$(MLX_DIR)
endif

INCLUDES    = -I$(INCDIR) -I$(LIBFTDIR) $(MLX_INC)

SUCCESS     = "\033[1;92m Compilation réussie ! ✅\033[0m"
FAILURE     = "\033[1;91m Erreur de compilation ! ❌\033[0m"
LIBFT_COMP  = "\033[1;94m Compilation de la libft... 🔨\033[0m"
CUBE_COMP   = "\033[1;94m Compilation de cube3d... 🔨\033[0m"
MLX_COMP    = "\033[1;94m Compilation de la MLX... 🔨\033[0m"
CLEAN_MSG   = "\033[1;93m Nettoyage des fichiers objets... 🧹\033[0m"
FCLEAN_MSG  = "\033[1;93m Nettoyage complet... 🧹\033[0m"

all: $(OBJ_DIRS) $(NAME)

$(OBJ_DIRS):
	@mkdir -p $@

$(NAME): $(OBJS) $(LIBFT) $(MLX_DIR)/libmlx.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;92m Compilation terminée ! ✅\033[0m"
	@echo "\033[1;96m"
	@echo "---------------------------------------------"
	@echo "██████╗██╗   ██╗██████╗     ██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗    ╚════██╗██╔══██╗"
	@echo "██║     ██║   ██║██████╔╝     █████╔╝██║  ██║"
	@echo "██║     ██║   ██║██╔══██╗     ╚═══██╗██║  ██║"
	@echo "╚██████╗╚██████╔╝██████╔╝    ██████╔╝██████╔╝"
	@echo " ╚═════╝ ╚═════╝ ╚═════╝     ╚═════╝ ╚═════╝ "
	@echo "---------------------------------------------"
	@echo "\033[0m"

$(LIBFT):
	@echo $(LIBFT_COMP)
	@make -C $(LIBFTDIR) > /dev/null 2>&1

$(MLX_DIR)/libmlx.a:
	@echo "Building MiniLibX in $(MLX_DIR)..."
	@$(MAKE) -C $(MLX_DIR) > /dev/null 2>&1

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)_bonus: $(BONUS_OBJS) $(LIBFT) $(MLX_DIR)/libmlx.a
	@$(CC) $(CFLAGS) $^ $(INCLUDES) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;92m Compilation bonus terminée ! ✅\033[0m"
	@echo "\033[1;96m"
	@echo "---------------------------------------------"
	@echo "██████╗██╗   ██╗██████╗     ██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗    ╚════██╗██╔══██╗"
	@echo "██║     ██║   ██║██████╔╝     █████╔╝██║  ██║"
	@echo "██║     ██║   ██║██╔══██╗     ╚═══██╗██║  ██║"
	@echo "╚██████╗╚██████╔╝██████╔╝    ██████╔╝██████╔╝"
	@echo " ╚═════╝ ╚═════╝ ╚═════╝     ╚═════╝ ╚═════╝ "
	@echo "---------------------------------------------"
	@echo "\033[0m"

clean:
	@echo $(CLEAN_MSG)
	@$(RM) -r $(OBJDIR) 2>/dev/null || true
	@find src -name '*.o' -delete
	@find src_bonus -name '*.o' -delete
	@make clean -C $(LIBFTDIR) > /dev/null 2>&1
	@make clean -C $(MLX_DIR) > /dev/null 2>&1

fclean: clean
	@echo $(FCLEAN_MSG)
	@$(RM) $(NAME) 2>/dev/null || true
	@find src -name '*.o' -delete
	@find src_bonus -name '*.o' -delete
	@make fclean -C $(LIBFTDIR) > /dev/null 2>&1
	@make clean -C $(MLX_DIR) > /dev/null 2>&1

re: fclean all

leaks: $(NAME)
	@echo "\033[1;94m Vérification des fuites mémoire... 🔍\033[0m"
ifeq ($(shell uname), Darwin)
	@leaks -atExit -- ./$(NAME) || true
else
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
endif

bonus: CFLAGS += -DBONUS
bonus: $(NAME)_bonus

.PHONY: all clean fclean re libft_make leaks bonus