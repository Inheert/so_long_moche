# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 14:27:18 by tclaereb          #+#    #+#              #
#    Updated: 2024/06/17 14:42:25 by tclaereb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

_SRCS = main.c \
		utils/ft_malloc.c \
		utils/garbage_collector.c \
		utils/short_utils.c \
		utils/short_utils2.c \
		utils/t_map/map_parsing.c \
		utils/t_map/map_new.c \
		utils/t_map/map_add_below.c \
		utils/t_map/map_add_right.c \
		utils/t_map/map_len.c \
		utils/t_map/map_link_lines.c \
		utils/t_map/map_validity.c \
		utils/t_map/map_validity2.c \
		mlx/mlx_init.c \
		mlx/mlx_hooks.c \
		mlx/moove_player.c \

SRCS_DIR = src

SRCS = $(addprefix $(SRCS_DIR)/, $(_SRCS))

SRCO = $(SRCS:.c=.o)

MAKE_LIBFT = $(MAKE) -C ./libft
LIBFT = ./libft/libft.a

FLAG = -Wall -Wextra -Werror
INC = -I includes/

all : $(NAME)

$(LIBFT):
	$(MAKE_LIBFT)

$(NAME) : $(SRCO) | $(LIBFT)
	cc $(FLAG) -o $(NAME) $(SRCO) $(LIBFT) MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

%.o : %.c
	cc $(FLAG) -c $< -o $@ $(INC)

clean :
	/bin/rm -f $(SRCO)
	$(MAKE_LIBFT) clean

fclean : clean
	/bin/rm -f $(NAME)
	$(MAKE_LIBFT) fclean

re :
	$(MAKE_LIBFT) fclean
	make fclean
	make

.PHONY: all clean fclean re

