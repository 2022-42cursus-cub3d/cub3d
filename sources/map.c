/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:01:52 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/17 15:07:50 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_content(void *content)
{
	free((char *)content);
	content = 0;
}

bool	chk_line(t_map *map, char *str)
{
	static bool	p_flag = false;
	int	idx;

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
		if (false == chk_line(map, line))
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
}

void	save_map(t_map *map)
{
	int		idx;
	size_t	cpy_num;
	t_list	*cur;

	idx = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->hei + 1));
	if (0 == map->map)
	{
		ft_lstclear(&(map->list), free_content);
		error(strerror(errno), 0);
	}
	map->map[map->hei] = 0;
	cur = map->list;
	while (idx < map->hei)
	{
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
		idx++;
		cur = cur->next;
	}
	ft_lstclear(&(map->list), free_content);
	print_map(map);
	printf("\n\n");
	replace_space(map);
}

void	replace_space(t_map *map)
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
	print_map(map);
	printf("dir: %c\n", map->dir);
}

void	print_map(t_map *map)
{
	int	idx;
	int j;

	idx = 0;
	while (map->map[idx])
	{
		j = 0;
		while (map->map[idx][j])
		{
			printf("%c", map->map[idx][j]);
			j++;
		}
		printf("\n");
		idx++;
	}
}
