/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:35:22 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/24 18:51:33 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_vertical(t_info *info, int direction)
{
	t_pos_d	tmp;

	tmp = info->vec.pos;
	tmp.x += direction * info->vec.dir.x * MV_SPEED;
	tmp.y += direction * info->vec.dir.y * MV_SPEED;
	if (info->map.map[(int)tmp.y][(int)tmp.x] != '1')
		info->vec.pos = tmp;
}

void	move_horizontal(t_info *info, int direction)
{
	t_pos_d	tmp;

	tmp = info->vec.pos;
	tmp.x += direction * info->vec.plane.x * MV_SPEED;
	tmp.y += direction * info->vec.plane.y * MV_SPEED;
	if (info->map.map[(int)tmp.y][(int)tmp.x] != '1')
		info->vec.pos = tmp;
}

void	rotate(t_vector *vec, int direction)
{
	t_pos_d	ret;
	t_pos_d	org;

	org = vec->dir;
	ret.x = org.x * cos(direction * RT_SPEED) - org.y * sin(direction * RT_SPEED);
	ret.y = org.x * sin(direction * RT_SPEED) + org.y * cos(direction * RT_SPEED);
	vec->dir = ret;
	org = vec->plane;
	ret.x = org.x * cos(direction * RT_SPEED) - org.y * sin(direction * RT_SPEED);
	ret.y = org.x * sin(direction * RT_SPEED) + org.y * cos(direction * RT_SPEED);
	vec->plane = ret;
}

void	move(t_info *info)
{
	if (info->key.w == true)
		move_vertical(info, 1);
	else if (info->key.s == true)
		move_vertical(info, -1);
	else if (info->key.a == true)
		move_horizontal(info, -1);
	else if (info->key.d == true)
		move_horizontal(info, 1);
	else if (info->key.left == true)
		rotate(&(info->vec), -1);
	else if (info->key.right == true)
		rotate(&(info->vec), 1);
}
