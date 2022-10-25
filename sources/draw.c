/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:56:52 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 19:43:20 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_background(t_info *info)
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
			dest = info->img.addr + (y * info->img.len
					+ x * (info->img.bpp / 8));
			if (y < HEI / 2)
				*(unsigned int *)dest = info->map.ceiling.rgb;
			else
				*(unsigned int *)dest = info->map.floor.rgb;
			y++;
		}
		x++;
	}
}

static void	draw_wall(t_info *info, t_vector *vec, t_draw *draw, t_map *map)
{
	int		x;
	int		y;
	char	*dst;

	x = -1;
	while (++x < WID)
	{
		set_vector(vec, x);
		dda(info, vec, draw);
		if ((vec->side == 0 && vec->rayDir.x > 0)
			|| (vec->side == 1 && vec->rayDir.y < 0))
			draw->tex.x = TEX_WID - draw->tex.x - 1;
		y = draw->draw_start - 1;
		set_wall_texture(info);
		while (++y < draw->draw_end)
		{
			draw->tex.y = (int)draw->tex_pos & (TEX_HEI - 1);
			draw->tex_pos += draw->step;
			draw->color = *(unsigned int *)(map->imgs[draw->wall_idx].addr
					+ (draw->tex.y * map->imgs[draw->wall_idx].len
						+ draw->tex.x * map->imgs[draw->wall_idx].bpp / 8));
			dst = info->img.addr + y * info->img.len + x * (info->img.bpp / 8);
			*(unsigned int *)dst = draw->color;
		}
	}
}

void	draw(t_info *info)
{
	draw_background(info);
	draw_wall(info, &(info->vec), &(info->draw), &(info->map));
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
