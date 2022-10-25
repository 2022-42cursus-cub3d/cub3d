/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:13:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 14:54:36 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	chk_empty_line(int fd, char **line)
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

static bool	chk_content(t_map *map, char *str)
{
	static bool	p_flag = false;
	int			idx;

	idx = -1;
	while (str[++idx])
	{
		if ('0' == str[idx] || '1' == str[idx] || ' ' == str[idx])
			continue ;
		else if ('N' == str[idx] || 'S' == str[idx] || 'W' == str[idx]
			|| 'E' == str[idx])
		{
			if (true == p_flag)
				return (false);
			map->dir = str[idx];
			p_flag = true;
		}
		else
			return (false);
	}
	return (true);
}

static bool	chk_map_line(t_map *map, char **line)
{
	if (0 == ft_strlen(*line))
	{
		if (true == chk_empty_line(map->fd, line))
			return (true);
		ft_lstclear(&(map->list), free_list_content);
		error("Map must have no empty lines", *line);
	}
	if (false == chk_content(map, *line))
	{
		ft_lstclear(&(map->list), free_list_content);
		error("The map must be composed of only 6 possible characters:\
		0, 1 and N, S, E or W", *line);
	}
	return (false);
}

void	save_map_to_list(t_map *map)
{
	char	*line;

	while (get_next_line(map->fd, &line) > 0)
	{
		if (0 != ft_strlen(line))
			break ;
		free(line);
	}
	map->list = ft_lstnew(line);
	while (get_next_line(map->fd, &line) > 0)
	{
		if (true == chk_map_line(map, &line))
			return ;
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
