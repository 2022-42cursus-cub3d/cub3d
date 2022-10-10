/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:19:40 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/10 22:04:33 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_bool	parse_err(char *err_msg, char *malloc_str)
{
	if (0 != malloc_str)
		free(malloc_str);
	printf("Error\n%s\n", err_msg);
	return (FALSE);
}

t_bool	is_parse_err(int argc, char **argv)
{
	char	*tmp;
	if (2 != argc)
		return (parse_err("Usage: ./cub3d \".cub_file_name\"", 0));
	if (4 > ft_strlen(argv[1]))
		return (parse_err("This program must take as a first argument a scene \
description file with the .cub extension!\n", 0));
	tmp = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (ft_strncmp(".cub", tmp, 4))
		return (parse_err("This program must take as a first argument a scene \
description file with the .cub extension!\n", tmp));
	free(tmp);
	if (FALSE == map_open(argv[1]))
		return (FALSE);
	return (save_map(argv[1]));
}

static	t_bool init_parse(char *str)
{
	int		idx;

	idx = 0;
	if (FALSE == map_open(str))
		return (FALSE);
	while (idx < info()->hei)
		get_next_line(info()->parse.fd, &(info()->map[idx++]));
}

t_bool	save_map(char *str)
{
	int		len;
	size_t	max;
	char	*line;

	len = 0;
	max = 0;
	line = 0;
	while (0 < get_next_line(info()->parse.fd, &line))
	{
		len++;
		max_num(&max, ft_strlen(line));
		free(line);
	}
	if (line)
	{
		len++;
		max_num(&max, ft_strlen(line));
		free(line);
	}
	close(info()->parse.fd);
	info()->hei = len;
	info()->map = (char **)malloc(sizeof(char *) * (len + 1));
	if (0 != info()->map)
		return (parse_err("malloc error", 0));
	info()->map[len] = 0;
	return (init_parse(str));
}
