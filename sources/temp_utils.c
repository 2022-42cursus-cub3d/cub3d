/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:56:47 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 14:53:30 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	leaks(void)
{
	system("leaks cub3D");
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
