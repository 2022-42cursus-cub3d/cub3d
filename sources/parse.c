/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:19:40 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/11 18:55:53 by hyojlee          ###   ########.fr       */
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

t_bool	chk_map_arg(char *str)
{
	char	*type;

	type = ft_substr(str, 0, 2);
	if (0 == info()->parse.imgs.num)
	{
		if (ft_strncmp("NO", type, 2))
			return (parse_err("순서 에러", type));
		free(type);
		type = ft_substr(str, 2, ft_strlen(str) - 2);
		info()->parse.imgs.north.img = mlx_xpm_file_to_image(info()->data.mlx
			, type, &(info()->parse.imgs.north.wid), &(info()->parse.imgs.north.hei));
	}
	else if (1 == info()->parse.imgs.num)
	{
		if (ft_strncmp("SO", type, 2))
			return (parse_err("순서 에러", type));
		free(type);
		type = ft_substr(str, 2, ft_strlen(str) - 2);
		info()->parse.imgs.south.img = mlx_xpm_file_to_image(info()->data.mlx
			, type, &(info()->parse.imgs.south.wid), &(info()->parse.imgs.south.hei));
		free(type);
		info()->parse.imgs.num++;
		
	}
	else if (2 == info()->parse.imgs.num)
	{
		if (ft_strncmp("WE", type, 2))
			return (parse_err("순서 에러", type));
		free(type);
		type = ft_substr(str, 2, ft_strlen(str) - 2);
		info()->parse.imgs.west.img = mlx_xpm_file_to_image(info()->data.mlx
			, type, &(info()->parse.imgs.west.wid), &(info()->parse.imgs.west.hei));
		free(type);
		info()->parse.imgs.num++;
	}
	else if (3 == info()->parse.imgs.num)
	{
		if (ft_strncmp("EA", type, 2))
			return (parse_err("순서 에러", type));
		free(type);
		type = ft_substr(str, 2, ft_strlen(str) - 2);
		info()->parse.imgs.east.img = mlx_xpm_file_to_image(info()->data.mlx
			, type, &(info()->parse.imgs.east.wid), &(info()->parse.imgs.east.hei));
		free(type);
		info()->parse.imgs.num++;	
	}
	free(type);
	info()->parse.imgs.num++;
	return (TRUE);
}

t_bool	save_map(char *str)
{
	char *str;

	str = 0;
	while (0 < get_next_line(info()->parse.fd, &str))
	{
		if (0 == ft_strlen(str))
			free(str);
		else if (FALSE == chk_map_arg(str))
		{
			free(str);
			return (FALSE);
		}
	}
}
