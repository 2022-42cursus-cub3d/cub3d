/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:35:22 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/20 15:42:45 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate(t_pos_d *pos, int direction)
{
	t_pos_d	ret;

	ret.x = pos->x * cos(direction * RT_SPEED) - pos->y * sin(direction * RT_SPEED);
	ret.y = pos->x * sin(direction * RT_SPEED) + pos->y * cos(direction * RT_SPEED);
	*pos = ret;
}
