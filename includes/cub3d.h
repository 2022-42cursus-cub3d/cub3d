/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:40:45 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/17 16:10:25 by hyojlee          ###   ########.fr       */
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

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC				53
# define KEY_W					13
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_LEFT				123
# define KEY_RIGHT				124

# define NO						0
# define SO						1
# define WE						2
# define EA						3

# define WID					640
# define HEI					480

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
	char	dir;

	t_img	imgs[4];
	t_rgb	floor;
	t_rgb	ceiling;

	t_list	*list;
	char	**map;
}	t_map;

typedef struct s_pos
{
	int		x;
	int		y;
}	t_pos;

typedef struct	s_key
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;

	bool	left;
	bool	right;
}	t_key;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	t_img	img;

	t_map	map;
	t_pos	pos;
	t_key	key;
}	t_info;

/*
** error.c
*/
void	error(char *err_msg, char *alloc_str);
int		terminate(t_info *info);

/*
** check.c
*/
void	chk_arg(int ac, char **av);
void	chk_file(t_map *map, char *av);
void	get_map_arg(t_info *info);

/*
** main.c
*/
void	leaks(void);

/*
** map.c
*/
void	save_map_to_list(t_info *info);
void	find_map_size(t_map *map);
void	save_map(t_map *map);
void	print_map(t_map *map);
void	replace_space(t_map *map);

/*
** free.c
*/
void	free_malloc(char **str, int num);

/*
** chk_valid.c
*/
void	chk_valid_map(t_info *info);

/*
** event.c
*/
int		key_press(int keycode, t_info *info);
int		key_release(int keycode, t_info *info);

/*
** draw.c
*/
int		draw_image(t_info *info);


#endif
