/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:38:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/11 23:32:07 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_bool	parse_err(char *err_msg, char *malloc_str)
{
	if (0 != malloc_str)
		free(malloc_str);
	printf("Error\n%s\n", err_msg);
	return (FALSE);
}

void	max_num(size_t *max, size_t num)
{
	if (*max < num)
		*max = num;
}

t_bool	map_open(char *str)
{
	info()->parse.fd = open(str, O_RDONLY);
	if (info()->parse.fd < 0)
		return (parse_err(strerror(errno), 0));
	return (TRUE);
}
