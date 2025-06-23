# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 14:54:30 by maximemarti       #+#    #+#              #
#    Updated: 2025/06/23 17:24:14 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cube3d

SRC         = src/main.c \
				src/split_map.c \
				src/assign_map.c \
				src/free.c \
              # ajoute ici les autres fichiers .c de ton projet

OBJ         = $(SRC:.c=.o)

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror

# Répertoires et librairies
LIBFT_DIR   = libft
MLX_DIR     = mlx

LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a

INCLUDES    = -I$(LIBFT_DIR) -I$(MLX_DIR)

MLX_FLAGS   = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Compilation terminée."

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C $(MLX_DIR)
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: fclean all