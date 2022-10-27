/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:01:52 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/27 13:30:53 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_map_size(t_map *map)
{
	t_list	*cur;
	int		len;

	cur = map->list;
	while (cur)
	{
		len = (int)ft_strlen((char *)cur->content);
		if (map->wid < len)
			map->wid = len;
		cur = cur->next;
		map->hei++;
	}
}

static void	replace_space(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (' ' == map->map[i][j])
				map->map[i][j] = 'b';
			j++;
		}
		i++;
	}
}

static void	save_map_line(t_map *map, t_list *cur, int idx)
{
	size_t	cpy_num;

	cpy_num = 0;
	map->map[idx] = (char *)malloc(sizeof(char) * (map->wid + 1));
	if (0 == map->map[idx])
	{
		free_malloc(map->map, idx);
		error(strerror(errno), 0);
	}
	ft_memset(map->map[idx], 'b', map->wid);
	map->map[idx][map->wid] = 0;
	cpy_num = ft_strlcpy(map->map[idx], (char *)cur->content, map->wid + 1);
	if ((int)cpy_num < map->wid)
		map->map[idx][cpy_num] = 'b';
}

void	save_map(t_map *map)
{
	int		idx;
	t_list	*cur;

	idx = 0;
	save_map_to_list(map);
	get_map_size(map);
	map->map = (char **)malloc(sizeof(char *) * (map->hei + 1));
	if (0 == map->map)
	{
		ft_lstclear(&(map->list), free_list_content);
		error(strerror(errno), 0);
	}
	map->map[map->hei] = 0;
	cur = map->list;
	while (idx < map->hei)
	{
		save_map_line(map, cur, idx);
		idx++;
		cur = cur->next;
	}
	ft_lstclear(&(map->list), free_list_content);
	replace_space(map);
}
