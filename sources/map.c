/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:01:52 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/16 17:20:40 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_content(void *content)
{
	free((char *)content);
	content = 0;
}

bool	chk_line(char *str)
{
	static bool	p_flag = false;
	int	idx;

	idx = -1;
	while (str[++idx])
	{
		if ('0' == str[idx] || '1' == str[idx] || ' ' == str[idx])
			continue ;
		else if ('N' == str[idx] || 'S' == str[idx] || 'E' == str[idx]
			|| 'W' == str[idx])
		{
			if (true == p_flag)
				return (false);
			p_flag = true;
		}
		else
			return (false);
	}
	return (true);
}

bool	chk_empty_line(int fd, char **line)
{
	free(*line);
	while (get_next_line(fd, line) > 0)
	{
		if (0 != ft_strlen(*line))
			return (false);
		free(*line);
	}
	if (*line)
	{
		if (0 != ft_strlen(*line))
			return (false);
		free(*line);
	}
	return (true);
}

void	save_map_to_list(t_info *info)
{
	t_map	*map;
	char	*line;

	map = &(info->map);
	while (get_next_line(map->fd, &line) > 0)
	{
		if (0 != ft_strlen(line))
			break ;
		free(line);
	}
	map->list = ft_lstnew(line);
	while (get_next_line(map->fd, &line) > 0)
	{
		if (0 == ft_strlen(line))
		{
			if (true == chk_empty_line(map->fd, &line))
				return ;
			ft_lstclear(&(map->list), free_content);
			error("Map must have no empty lines", line);
		}
		if (false == chk_line(line))
		{
			ft_lstclear(&(map->list), free_content);
			error("The map must be composed of only 6 possible characters: 0, 1 and N, S, E or W", line);
		}
		ft_lstadd_back(&(map->list), ft_lstnew(line));
	}
	if (line)
	{
		if (0 == ft_strlen(line))
			free(line);
		else
			ft_lstadd_back(&(map->list), ft_lstnew(line));
	}
}

void	find_map_size(t_map *map)
{
	t_list	*cur;

	cur = map->list;
	while (cur)
	{
		if (map->wid < (int)ft_strlen((char *)(cur->content)))
			map->wid = (int)ft_strlen((char *)(cur->content));
		cur = cur->next;
		map->hei++;
	}
	printf("%d %d\n", map->wid, map->hei);
	ft_lstclear(&(map->list), free_content);
}
