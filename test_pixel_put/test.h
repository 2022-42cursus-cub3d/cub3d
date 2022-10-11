/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:13:24 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/11 15:07:41 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../minilibx_opengl_20191021/mlx.h"
# include <stdlib.h>

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define KEY_ESC			53
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2

typedef struct s_data {
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
}	t_data;

#endif
