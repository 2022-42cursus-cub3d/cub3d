/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:56:52 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/17 16:36:20 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_background(t_info *info)
{
	char	*dest;
	int		x;
	int		y;

	x = 0;
	while (x < WID)
	{
		y = 0;
		while (y < HEI)
		{
			dest = info->img.addr + (y * info->img.line_len + x * (info->img.bpp / 8));
			if (y < HEI / 2)
				*(unsigned int *)dest = info->map.ceiling.rgb;
			else
				*(unsigned int *)dest = info->map.floor.rgb;
			y++;
		}
		x++;
	}
}

int	draw_image(t_info *info)
{
	draw_background(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
	return (0);
}

