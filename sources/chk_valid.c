/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:14:55 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/27 15:02:46 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	chk_surround(t_map *map, int i, int j)
{
	if (i == 0 || i == map->hei - 1 
		|| j == 0 || j == map->wid - 1)
	{
		free_malloc(map->map, map->hei);
		error("Invalid map", 0);
	}
	if ((i > 0 && BLANK == map->map[i - 1][j])
		|| (i + 1 < map->hei && BLANK == map->map[i + 1][j])
		|| (j > 0 && BLANK == map->map[i][j - 1])
		|| (j + 1 < map->wid && BLANK == map->map[i][j + 1]))
	{
		free_malloc(map->map, map->hei);
		error("Invalid map", 0);
	}
}

void	chk_valid_map(t_info *info)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	map = &(info->map);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if ('0' == map->map[i][j] || map->dir == map->map[i][j])
			{
				chk_surround(map, i, j);
				if (map->dir == map->map[i][j])
				{
					info->vec.pos.x = (double)j;
					info->vec.pos.y = (double)i;
				}
			}
			j++;
		}
		i++;
	}
}

void	init_dir_vec(t_info *info)
{
	info->vec.dir.x = 0;
	info->vec.dir.y = 0;
	info->vec.plane.x = 0;
	info->vec.plane.y = 0;
	if ('N'== info->map.dir)
	{
		info->vec.dir.y = -1;
		info->vec.plane.x = 0.66;
	}
	else if ('S' == info->map.dir)
	{
		info->vec.dir.y = 1;
		info->vec.plane.x = -0.66;
	}
	else if ('W' == info->map.dir)
	{
		info->vec.dir.x = -1;
		info->vec.plane.y = -0.66;
	}
	else if ('E' == info->map.dir)
	{
		info->vec.dir.x = 1;
		info->vec.plane.y = 0.66;
	}
}