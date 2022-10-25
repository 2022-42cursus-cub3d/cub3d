/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:41:39 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 14:54:33 by hyojlee          ###   ########.fr       */
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

void	free_list_content(void *content)
{
	free((char *)content);
	content = 0;
}

void	error(char *err_msg, char *alloc_str)
{
	if (0 != alloc_str)
		free(alloc_str);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	atexit(leaks);
	exit(1);
}

int	terminate(t_info *info)
{
	mlx_destroy_image(info->mlx, info->img.img);
	mlx_destroy_window(info->mlx, info->win);
	free_malloc(info->map.map, info->map.hei);
	close(info->map.fd);
	atexit(leaks);
	exit(0);
	return (0);
}
