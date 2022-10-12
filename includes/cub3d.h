/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:40:45 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/11 23:32:17 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <errno.h>
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
	int			num;
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

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;

	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_data;

typedef struct s_info
{
	t_data		data;
	int			wid;
	int			hei;

	t_parse		parse;
	t_list		*list;
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

/*
** parse_utils.c
*/
t_bool	parse_err(char *err_msg, char *malloc_str);
void	max_num(size_t *max, size_t num);
t_bool	map_open(char *str);

#endif
