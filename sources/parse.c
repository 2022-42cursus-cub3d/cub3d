/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:19:40 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/06 20:30:57 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool	is_parse_err(int argc, char **argv)
{
	if (2 != argc)
	{
		printf("Error\n");
		printf("Usage: ./cub3d \".cub_file_name\"\n");
		return (FALSE);
	}
	if (4 > ft_strlen(argv[1]))
	{
		printf("Error\n");
		printf("This program must take as a first argument a scene description \
file with the .cub extension!\n");
		return (FALSE);
	}
	return (TRUE);
}
