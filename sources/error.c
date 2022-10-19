/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:41:39 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/19 19:29:38 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(char *err_msg, char *alloc_str)
{
	if (0 != alloc_str)
		free(alloc_str);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	exit(1);
}

int	terminate(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img.img);
	mlx_destroy_window(info->mlx, info->win);
	free_malloc(info->map.map, info->map.hei);
	exit(0);
	return (0);
}
