# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2022/10/24 19:00:51 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror
MAKE = make
NAME = cub3D
MLX = -I./minilibx_opengl_20191021 -L./minilibx_opengl_20191021 -lmlx
LIBFT_GNL = -I./libft_gnl -I./libft_gnl/get_next_line -L./libft_gnl -lft_gnl
INC = -I./includes
FRAMEWORK = -framework OpenGL -framework Appkit
SRC = ./sources
SRCS = ${SRC}/main.c		\
		${SRC}/chk_arg.c	\
		${SRC}/error.c		\
		${SRC}/map.c		\
		${SRC}/free.c		\
		${SRC}/hook.c		\
		${SRC}/draw.c		\
		${SRC}/move.c		\
		${SRC}/chk_valid.c
OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME) : $(OBJS) ./libft_gnl/libft_gnl.a ./minilibx_opengl_20191021/libmlx.a
	$(CC) $(CFLAGS) $(MLX) $(LIBFT_GNL) $(FRAMEWORK) $(INC) $(OBJS) -o $(NAME)

./libft_gnl/libft_gnl.a :
	$(MAKE) -C ./libft_gnl bonus

./minilibx_opengl_20191021/libmlx.a :
	$(MAKE) -C ./minilibx_opengl_20191021 all

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(MAKE) -C ./libft_gnl clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ./libft_gnl fclean
	$(MAKE) -C ./minilibx_opengl_20191021 clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
