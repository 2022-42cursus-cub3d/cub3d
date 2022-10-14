/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:40:54 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/14 18:54:13 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	chk_arg(int ac, char **av)
{
	if (2 != ac || 4 > ft_strlen(av[1])
		|| ft_strncmp(".cub", av[1] + (ft_strlen(av[1]) - 4), 4))
		error("The program must take a .cub file.", 0);
}

void	chk_file(t_map *map, char *av)
{
	map->fd = open(av, O_RDONLY);
	if (map->fd < 0)
		error(strerror(errno), 0);
}

bool	is_empty_type(t_map *map)
{
	int	idx;

	idx = 0;
	while (idx < 4)
	{
		if (NULL != map->imgs[idx].img)
			return (false);
		idx++;
	}
	if (-1 != map->floor.rgb || -1 != map->ceiling.rgb)
		return (false);
	return (true);
}

bool	is_filled_all(t_map *map)
{
	int	idx;

	idx = 0;
	while (idx < 4)
	{
		if (NULL == map->imgs[idx].img)
			return (false);
		idx++;
	}
	if (-1 == map->floor.rgb || -1 == map->ceiling.rgb)
		return (false);
	return (true);
}

int	find_type(char *line)
{
	static char	*ids[] = { "NO", "SO", "WE", "EA", "F ", "C " };
	int			idx;

	idx = 0;
	while (idx < 6)
	{
		if (!ft_strncmp(ids[idx], line, 2))
			return (idx);
		idx++;
	}
	return (-1);
}

void	save_img(t_info *info, int idx, char *path)
{
	t_img	*simg;

	simg = &(info->map.imgs[idx]);
	if (0 == idx && false == is_empty_type(&(info->map)))
		error("Type identifiers must be followed a strict order.", path - 3);
	if (0 <= idx - 1 && NULL == info->map.imgs[idx - 1].img)
		error("Type identifiers must be followed a strict order.", path - 3);
	if (NULL != simg->img)
		error("Type information is duplicated.", path - 3);
	simg->img = mlx_xpm_file_to_image(info->mlx, path, &(simg->wid)
		, &(simg->hei));
	if (NULL == simg->img)
		error("Texture file error", path - 3);
	simg->addr = mlx_get_data_addr(simg->img, &(simg->bpp), &(simg->line_len)
		, &(simg->endian));
}

bool	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/*
** rgb의 rgb는 -1로 초기화되어 있다고 가정
*/
void	save_rgb(t_map *map, int tidx, char *str)
{
	t_rgb	*rgb;
	char	**split;
	int		idx;

	idx = 0;
	rgb = &(map->floor);
	if (tidx == 5)
		rgb = &(map->ceiling);
	if (-1 != rgb->rgb)
		error("Type information is duplicated.", str - 2);
	split = ft_split(str, ',');
	while (split[idx])
	{
		if (false == is_number(split[idx]))
			break ;
		rgb->rgbs[idx] = ft_atoi(split[idx]);
		if (rgb->rgbs[idx] > 256 || rgb->rgbs[idx] < 0)
			break ;
		idx++;
	}
	idx = 0;
	while (split[idx])
		free(split[idx++]);
	free(split);
	if (idx != 3)
		error("R, G, B colors in range [0, 255].", str - 2);
	rgb->rgb = (rgb->rgbs[0] << 16) + (rgb->rgbs[1] << 8) + rgb->rgbs[2];
}

void	get_map_arg(t_info *info)
{
	t_map	*map;
	char	*line;
	int		idx;

	map = &(info->map);
	line = 0;
	while (get_next_line(map->fd, &line) > 0)
	{
		if (0 == ft_strlen(line))
		{
			free(line);
			continue ;
		}
		idx = find_type(line);
		if (idx < 6)
		{
			if (idx < 0)
				error("Map error", line);
			else if (idx < 4)
				save_img(info, idx, line + 3);
			else if ((idx == 4 || idx == 5))
				save_rgb(map, idx, line + 2);
			if (idx == 5) // 천장 정보까지 다 읽었으면 gnl을 멈춰야함(이제부터 content 읽기)
				break ;
		}
		free(line);
	}
	if (false == is_filled_all(map))
		error("Lack of map information", 0);
}
