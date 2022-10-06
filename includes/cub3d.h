/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:40:45 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/06 20:29:35 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
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
	int	x;
	int	y;
}		t_pos;

typedef struct s_xpm
{
	int		wid;
	int		hei;
	void	*img;
}			t_xpm;

typedef struct s_xpmImgs
{
	t_xpm	wall;
	t_xpm	btm;
	t_xpm	plyr;
	t_xpm	clt;
	t_xpm	exit;
}			t_xpmImgs;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	void		*img;

	int			wid;
	int			hei;
	char		**map;

	int			steps;
	t_xpmImgs	imgs;
	t_pos		pos;
}			t_info;

/*
** utils.c
*/
t_info	*info(void);

/*
** parse.c
*/
t_bool is_parse_err(int argc, char **argv);

#endif
