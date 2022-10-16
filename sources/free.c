/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:55:03 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/17 00:56:36 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_malloc(char **str, int num)
{
	int	idx;

	idx = 0;
	while (idx < num)
		free(str[idx++]);
	free(str);
}
