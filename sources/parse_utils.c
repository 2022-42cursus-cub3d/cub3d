/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:38:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/10 21:58:22 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	max_num(size_t *max, size_t num)
{
	if (*max < num)
		*max = num;
}

t_bool	map_open(char *str)
{
	info()->parse.fd = open(str, O_RDONLY);
	if (info()->parse.fd < 0)
	{
		perror("Error\n");
		return (FALSE);
	}
	return (TRUE);
}
