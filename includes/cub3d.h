/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:40:45 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/10 19:00:20 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft_gnl/libft.h"
# include "../libft_gnl/get_next_line/get_next_line.h"
# include "../minilibx_opengl_20191021/mlx.h"

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define KEY_ESC			53
# define KEY_W				13
# define KEY_A				0
# define KEY_S				1
# define KEY_D				2
# define KEY_LEFT			123
# define KEY_RIGHT			124

typedef enum e_bool
{
	TRUE = 0,
	FALSE
}	t_bool;

typedef struct s_pos
{
	int			x;
	int			y;
}	t_pos;

typedef struct s_xpm
{
	int			wid;
	int			hei;
	void		*img;
}	t_xpm;

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}	t_rgb;

typedef struct s_xpmImgs
{
	t_xpm		north;
	t_xpm		south;
	t_xpm		west;
	t_xpm		east;
}	t_xpmImgs;

typedef struct s_parse
{
	int			fd;
	t_xpmImgs	imgs;
	t_rgb		f_rgb;
	t_rgb		c_rgb;
	int			maxLen;
}	t_parse;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	void		*img;

	int			wid;
	int			hei;

	t_parse		parse;
	char		**map;

	t_pos		pos;
}	t_info;

/*
** utils.c
*/
t_info	*info(void);

/*
** parse.c
*/
t_bool	is_parse_err(int argc, char **argv);
t_bool	init_parse(void);

#endif
