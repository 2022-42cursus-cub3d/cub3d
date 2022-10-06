# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2022/10/06 18:38:40 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make
NAME = cub3d
MLX = -I./minilibx_opengl_20191021 -L./minilibx_opengl_20191021 -lmlx
LIBFT_GNL = -I./libft_gnl -I./libft_gnl/get_next_line -L./libft_gnl -lft_gnl
INC = -I./includes
FRAMEWORK = -framework OpenGL -framework Appkit
SRC = ./sources
SRCS = ${SRC}/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME) : $(OBJS) ./libft_gnl/libft_gnl.a ./minilibx_opengl_20191021/libmlx.a
	$(CC) $(CFLAGS) $(MLX) $(LIBFT_GNL) $(FRAMEWORK) $(INC) $(OBJS) -o $(NAME)

./libft_gnl/libft_gnl.a :
	$(MAKE) -C ./libft_gnl all

./opengl/libmlx.a :
	$(MAKE) -C ./minilibx_opengl_20191021 all

%.o : %.c
	$(CC) -o $@ -c $<

clean:
	$(MAKE) -C ./libft_gnl clean
	$(MAKE) -C ./minilibx_opengl_20191021 clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C ./libft_gnl fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
