/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:36:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 19:05:44 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_info *info)
{
	if (keycode == KEY_W)
		info->key.w = true;
	else if (keycode == KEY_A)
		info->key.a = true;
	else if (keycode == KEY_S)
		info->key.s = true;
	else if (keycode == KEY_D)
		info->key.d = true;
	else if (keycode == KEY_LEFT)
		info->key.left = true;
	else if (keycode == KEY_RIGHT)
		info->key.right = true;
	else if (keycode == KEY_ESC)
		terminate(info);
	return (0);
}

int	key_release(int keycode, t_info *info)
{
	if (keycode == KEY_W)
		info->key.w = false;
	else if (keycode == KEY_A)
		info->key.a = false;
	else if (keycode == KEY_S)
		info->key.s = false;
	else if (keycode == KEY_D)
		info->key.d = false;
	else if (keycode == KEY_LEFT)
		info->key.left = false;
	else if (keycode == KEY_RIGHT)
		info->key.right = false;
	return (0);
}

int	game_loop(t_info *info)
{
	move(info);
	draw(info);
	return (0);
}
