/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:14:55 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/19 19:16:48 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
				if (i == 0 || i == map->hei - 1 
					|| j == 0 || j == map->wid - 1)
				{
					free_malloc(map->map, map->hei);
					error("Invalid map", 0);
				}
				if ((i > 0 && 'b' == map->map[i - 1][j])
					|| (i + 1 < map->hei && 'b' == map->map[i + 1][j])
					|| (j > 0 && 'b' == map->map[i][j - 1])
					|| (j + 1 < map->wid && 'b' == map->map[i][j + 1]))
				{
					free_malloc(map->map, map->hei);
					error("Invalid map", 0);
				}
				if (map->dir == map->map[i][j])
				{
					info->pos.x = (double)j;
					info->pos.y = (double)i;
				}
			}
			j++;
		}
		i++;
	}
}
