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
INCDIR      = includes
LIBFTDIR    = libft
MLX_DIR     = mlx_linux

SRC_FILES   = main.c \
				events/e_window.c \
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
				render/r_loop.c \
				render/r_textures.c \
				utils/u_cleanup.c \
				utils/u_dir_player.c \
				print.c

SRCS        = $(addprefix $(SRCDIR)/, $(SRC_FILES))
OBJS        = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJ_DIRS    = $(sort $(dir $(OBJS)))

LIBFT       = $(LIBFTDIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

INCLUDES    = -I$(INCDIR) -I$(LIBFTDIR) -I$(MLX_DIR)
MLX_FLAGS   = -lX11 -lXext -lXpm -lGL -lm

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

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo $(CUBE_COMP)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)
	@echo $(SUCCESS)
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

$(MLX):
	@echo $(MLX_COMP)
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo $(CLEAN_MSG)
	@$(RM) -r $(OBJDIR) 2>/dev/null || true
	@make clean -C $(LIBFTDIR) > /dev/null 2>&1
	@make clean -C $(MLX_DIR) > /dev/null 2>&1

fclean: clean
	@echo $(FCLEAN_MSG)
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTDIR) > /dev/null 2>&1

re: fclean all

leaks: $(NAME)
	@echo "\033[1;94m Vérification des fuites mémoire... 🔍\033[0m"
ifeq ($(shell uname), Darwin)
	@leaks -atExit -- ./$(NAME) || true
else
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)
endif

.PHONY: all clean fclean re libft_make leaks

