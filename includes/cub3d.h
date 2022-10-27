/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:40:45 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/26 21:05:15 by hyojlee          ###   ########.fr       */
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

# define WID					1240
# define HEI					880

# define TEX_WID				64
# define TEX_HEI				64

# define MV_SPEED				0.05
# define RT_SPEED				0.03

typedef struct s_img
{
	void		*img;
	int			wid;
	int			hei;

	char		*addr;
	int			bpp;
	int			len;
	int			endian;
}	t_img;

typedef struct s_rgb
{
	int			rgbs[3];
	int			rgb;
}	t_rgb;

typedef struct s_map
{
	int			fd;
	int			wid;
	int			hei;
	char		dir;

	t_img		imgs[4];
	t_rgb		floor;
	t_rgb		ceiling;

	t_list		*list;
	char		**map;
}	t_map;

typedef struct s_pos_i
{
	int			x;
	int			y;
}	t_pos_i;

typedef struct s_pos_d
{
	double		x;
	double		y;
}	t_pos_d;

typedef struct s_key
{
	bool		w;
	bool		a;
	bool		s;
	bool		d;

	bool		left;
	bool		right;
}	t_key;

typedef struct s_vector
{
	t_pos_d		pos;
	t_pos_d		dir;
	t_pos_d		plane;
	t_pos_i		map;
	t_pos_i		step;
	int			side;
	double		camera_x;
	t_pos_d		ray_dir;
	t_pos_d		side_dist;
	t_pos_d		delta_dist;
	double		perp_wall_dist;
}	t_vector;

typedef struct s_draw
{
	int			line_hei;
	int			draw_start;
	int			draw_end;
	int			wall_idx;
	double		wall_x;
	double		tex_pos;
	double		step;
	int			color;
	t_pos_i		tex;
}	t_draw;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_img		img;

	t_map		map;
	t_vector	vec;
	t_key		key;
	t_draw		draw;
}	t_info;

/*
** temp_utils.c
*/
void	leaks(void);
void	print_map(t_map *map);

/*
** utils.c
*/
void	free_malloc(char **str, int num);
void	free_list_content(void *content);
void	error(char *err_msg, char *alloc_str);
int		terminate(t_info *info);

/*
** chk_utils.c
*/
int		find_type(char *line, int idx);
bool	is_number(char *str);
void	free_split(char **split);

/*
** chk_map_arg.c
*/
void	chk_arg(int ac, char **av, t_map *map);
void	save_map_arg(t_info *info);

/*
** map_list.c
*/
void	save_map_to_list(t_map *map);

/*
** map.c
*/
void	save_map(t_map *map);

/*
** chk_valid.c
*/
void	chk_valid_map(t_info *info);
void	init_dir_vec(t_info *info);

/*
** hook.c
*/
int		key_press(int keycode, t_info *info);
int		key_release(int keycode, t_info *info);
int		game_loop(t_info *info);

/*
** draw_utils.c
*/
void	set_vector(t_vector *vec, int x);
void	dda(t_info *info, t_vector *vec, t_draw *draw);
void	set_wall_texture(t_info *info);

/*
** draw.c
*/
void	draw(t_info *info);

/*
** move.c
*/
void	move(t_info *info);

#endif
