# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/03 10:49:43 by hyojlee           #+#    #+#              #
#    Updated: 2022/10/11 14:20:29 by hyojlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
MAKE = make
NAME = test
MLX = -I../minilibx_opengl_20191021 -L../minilibx_opengl_20191021 -lmlx
FRAMEWORK = -framework OpenGL -framework Appkit

INC = -I./
SRCS = test.c
OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME) : $(OBJS) ../minilibx_opengl_20191021/libmlx.a
	$(CC) $(CFLAGS) $(INC) $(MLX) $(FRAMEWORK) $(OBJS) -o $(NAME)

../minilibx_opengl_20191021/libmlx.a :
	$(MAKE) -C ../minilibx_opengl_20191021 all

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	$(MAKE) -C ../minilibx_opengl_20191021 clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
