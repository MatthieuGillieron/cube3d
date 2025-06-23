# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 14:54:30 by maximemarti       #+#    #+#              #
#    Updated: 2025/06/23 14:54:38 by maximemarti      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d
SRC = main.c
MLX = mlx/libmlx.a
INC = -Imlx
FLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -framework OpenGL -framework AppKit

all:
	@make -C mlx
	@gcc $(FLAGS) $(SRC) $(MLX) $(INC) $(MLX_FLAGS) -o $(NAME)

clean:
	@make clean -C mlx

fclean: clean
	@rm -f $(NAME)

re: fclean all