/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:40:54 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/26 20:43:28 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_type(char *line, int idx)
{
	static char	*ids[] = {"NO", "SO", "WE", "EA", "F ", "C "};
	int			t_idx;

	t_idx = 0;
	while (t_idx < 6)
	{
		if (!ft_strncmp(ids[t_idx], line, 2))
		{
			if (idx > t_idx)
				error("Type information is duplicated.", line);
			else if (idx < t_idx)
			{
				error("Type identifiers must be followed a strict order.",
					line);
			}
			return (t_idx);
		}
		t_idx++;
	}
	error("Map error", line);
	return (-1);
}

bool	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	free_split(char **split)
{
	int	idx;

	idx = 0;
	while (split[idx])
		free(split[idx++]);
	free(split);
}
