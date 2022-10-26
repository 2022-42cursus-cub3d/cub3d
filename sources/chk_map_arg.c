/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_map_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:10:59 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/26 20:41:09 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	chk_arg(int argc, char **argv, t_map *map)
{
	if (2 != argc || 4 > ft_strlen(argv[1])
		|| ft_strncmp(".cub", argv[1] + (ft_strlen(argv[1]) - 4), 4))
		error("The program must take a .cub file.", 0);
	map->fd = open(argv[1], O_DIRECTORY);
	if (map->fd > 0)
	{
		close(map->fd);
		error("The program must take a .cub file.", 0);
	}
	map->fd = open(argv[1], O_RDONLY);
	if (map->fd < 0)
		error(strerror(errno), 0);
}

static void	save_img(t_info *info, int idx, char *path)
{
	t_img	*simg;

	simg = &(info->map.imgs[idx]);
	if (NULL != simg->img)
		error("Type information is duplicated.", path - 3);
	simg->img = mlx_xpm_file_to_image(info->mlx, path, &(simg->wid),
			&(simg->hei));
	if (NULL == simg->img)
		error("Texture file error", path - 3);
	simg->addr = mlx_get_data_addr(simg->img, &(simg->bpp), &(simg->len),
			&(simg->endian));
}

static void	save_rgb(t_map *map, int tidx, char *str)
{
	t_rgb	*rgb;
	char	**split;
	int		idx;

	idx = -1;
	rgb = &(map->floor);
	if (tidx == 5)
		rgb = &(map->ceiling);
	split = ft_split(str, ',');
	while (split[++idx])
	{
		if (false == is_number(split[idx]))
			break ;
		rgb->rgbs[idx] = ft_atoi(split[idx]);
		if (rgb->rgbs[idx] > 255 || rgb->rgbs[idx] < 0)
			break ;
	}
	free_split(split);
	if (idx > 3)
		error("Incorrect color information", str - 2);
	if (idx != 3)
		error("R, G, B colors in range [0, 255].", str - 2);
	rgb->rgb = (rgb->rgbs[0] << 16) + (rgb->rgbs[1] << 8) + rgb->rgbs[2];
}

void	save_map_arg(t_info *info)
{
	char	*line;
	int		type;
	int		idx;

	line = 0;
	idx = 0;
	while (get_next_line(info->map.fd, &line) > 0)
	{
		if (0 == ft_strlen(line))
		{
			free(line);
			continue ;
		}
		type = find_type(line, idx);
		if (idx < 4)
			save_img(info, type, line + 3);
		else if (idx == 4 || idx == 5)
			save_rgb(&(info->map), type, line + 2);
		free(line);
		if (idx++ == 5)
			break ;
	}
}
