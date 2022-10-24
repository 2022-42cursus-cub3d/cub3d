/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:56:52 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/24 15:04:00 by hyojlee          ###   ########.fr       */
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

void	chk_hit(t_info *info)
{
	t_vector	*vec;
	int			hit;

	hit = 0;
	vec = &(info->vec);
	while (hit == 0)
	{
		if (vec->side_dist.x < vec->side_dist.y)
		{
			vec->side_dist.x += vec->delta_dist.x;
			vec->map.x += vec->step.x;
			vec->side = 0;
		}
		else
		{
			vec->side_dist.y += vec->delta_dist.y;
			vec->map.y += vec->step.y;
			vec->side = 1;
		}
		if (info->map.map[vec->map.y][vec->map.x] == '1')
			hit = 1;
	}
	if (vec->side == 0)
		vec->perp_wall_dist = (vec->map.x - vec->pos.x + (1 - vec->step.x) / 2) / vec->rayDir.x;
	else 
		vec->perp_wall_dist = (vec->map.y - vec->pos.y + (1 - vec->step.y) / 2) / vec->rayDir.y; 
}

void	dda(t_info *info)
{
	t_vector	*vec;
	int			x;

	x = 0;
	vec = &(info->vec);
	while (x < WID)
	{
		vec->cameraX = 2 * x / (double)WID - 1;
		vec->rayDir.x = vec->dir.x + vec->plane.x * vec->cameraX;
		vec->rayDir.y = vec->dir.y + vec->plane.y * vec->cameraX;
		vec->map.x = (int)vec->pos.x;
		vec->map.y = (int)vec->pos.y;
		vec->delta_dist.x = fabs(1 / vec->rayDir.x);
		vec->delta_dist.y = fabs(1 / vec->rayDir.y);
		if (vec->rayDir.x < 0)
		{
			vec->step.x = -1;
			vec->side_dist.x = (vec->pos.x - vec->map.x) * vec->delta_dist.x;
		}
		else
		{
			vec->step.x = 1;
			vec->side_dist.x = (vec->map.x + 1 - vec->pos.x) * vec->delta_dist.x;
		}
		if (vec->rayDir.y < 0)
		{
			vec->step.y = -1;
			vec->side_dist.y = (vec->pos.y - vec->map.y) * vec->delta_dist.y;
		}
		else
		{
			vec->step.y = 1;
			vec->side_dist.y = (vec->map.y + 1 - vec->pos.y) * vec->delta_dist.y;
		}
		chk_hit(info);
	}
}

void	draw_image(t_info *info)
{
	draw_background(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

