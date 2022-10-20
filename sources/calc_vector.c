/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:14:48 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/20 15:35:02 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_pos_d	vector_add(t_pos_d pos1, t_pos_d pos2)
{
	pos1.x += pos2.x;
	pos1.y += pos2.y;
	return (pos1);
}

double	vector_inner_product(t_pos_d pos1, t_pos_d pos2)
{
	double	ret;

	ret = pos1.x * pos2.x + pos1.y * pos2.y;
	return (ret);
}

double	distance(t_pos_d pos)
{
	double	ret;

	ret = sqrt(pow(pos.x, 2) + pow(pos.y, 2));
	return (ret);
}

void	normalize(t_pos_d *pos)
{
	pos->x /= distance(*pos);
	pos->y /= distance(*pos);
}
