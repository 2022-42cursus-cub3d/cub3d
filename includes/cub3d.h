/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:40:45 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/14 17:18:49 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
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

typedef struct	s_img
{
	void	*img;
	int		wid;
	int		hei;

	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct	s_rgb
{
	int		rgbs[3];
	int		rgb;
}	t_rgb;

typedef struct s_map
{
	int		fd;
	int		wid;
	int		hei;
	int		flags;

	t_img	imgs[4];
	t_rgb	floor;
	t_rgb	ceiling;

	t_list	*list;
	char	**map;
}	t_map;

typedef struct s_pos
{
	int			x;
	int			y;
}	t_pos;

typedef struct s_info
{
	void	*mlx;
	void	*win;

	t_map	map;
	t_pos	pos;
}	t_info;

/*
** error.c
*/
void	error(char *err_msg, char *alloc_str);

/*
** 
*/
void	chk_arg(int ac, char **av);
void	chk_file(t_map *map, char *av);
void	get_map_arg(t_info *info);

// /*
// ** utils.c
// */
// t_info	*info(void);

// /*
// ** parse.c
// */
// bool	is_parse_err(int argc, char **argv);

// /*
// ** parse_utils.c
// */
// bool	parse_err(char *err_msg, char *malloc_str);
// void	max_num(size_t *max, size_t num);
// bool	map_open(char *str);

#endif
