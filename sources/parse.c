/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:19:40 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/10 19:05:09 by hyojlee          ###   ########.fr       */
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
	info()->parse.fd = open(argv[1], O_RDONLY);
	if (info()->parse.fd < 0)
	{
		perror("Error");
		return (FALSE);
	}
	return (init_parse());
}

t_bool	init_parse(void)
{
	int		len;
	size_t	max;
	char	*line;

	len = 0;
	max = 0;
	while (-1 != get_next_line(info()->parse.fd, &line))
	{
		len++;
		if (max < ft_strlen(line))
			max = ft_strlen(line);
		printf("%s\n", line);
		free(line);
	}
	info()->hei= len;
	return (TRUE);
}
