/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 18:33:17 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 19:17:02 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_step(t_vector *vec)
{
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
}

void	set_vector(t_vector *vec, int x)
{
	vec->cameraX = 2 * x / (double)WID - 1;
	vec->rayDir.x = vec->dir.x + vec->plane.x * vec->cameraX;
	vec->rayDir.y = vec->dir.y + vec->plane.y * vec->cameraX;
	vec->map.x = (int)vec->pos.x;
	vec->map.y = (int)vec->pos.y;
	vec->delta_dist.x = fabs(1 / vec->rayDir.x);
	vec->delta_dist.y = fabs(1 / vec->rayDir.y);
	set_step(vec);
}

static void	chk_hit(t_info *info)
{
	t_vector	*vec;
	int			hit;

	hit = 0;
	vec = &(info->vec);
	while (0 == hit)
	{
		if (vec->side_dist.x < vec->side_dist.y) // 기울기가 1보다 큼
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
		if ('1' == info->map.map[vec->map.y][vec->map.x])
			hit = 1;
	}
}

void	dda(t_info *info, t_vector *vec, t_draw *draw)
{
	chk_hit(info);
	if (vec->side == 0)
		vec->perp_wall_dist = (vec->map.x - vec->pos.x + (1 - vec->step.x) / 2) / vec->rayDir.x;
	else 
		vec->perp_wall_dist = (vec->map.y - vec->pos.y + (1 - vec->step.y) / 2) / vec->rayDir.y; 
	draw->line_hei = (int)(HEI / vec->perp_wall_dist);
	draw->draw_start = (HEI / 2) - (draw->line_hei / 2);
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = (HEI / 2) + (draw->line_hei / 2);
	if (draw->draw_end >= HEI)
		draw->draw_end = HEI - 1;
	if (vec->side == 0)
		draw->wallX = vec->pos.y + vec->perp_wall_dist * vec->rayDir.y;
	else
		draw->wallX = vec->pos.x + vec->perp_wall_dist * vec->rayDir.x;
	draw->wallX -= floor(draw->wallX);
	draw->tex.x = (int)(draw->wallX * (double)TEX_WID);
	draw->step = 1.0 * TEX_HEI / draw->line_hei;
	draw->tex_pos = (draw->draw_start - (HEI / 2 - draw->line_hei / 2)) * draw->step;
}

void	set_wall_texture(t_info *info)
{
	if (0 == info->vec.side && 1 == info->vec.step.x)
		info->draw.wall_idx = EA;
	else if (0 == info->vec.side && -1 == info->vec.step.x)
		info->draw.wall_idx = WE;
	else if (1 == info->vec.side && 1 == info->vec.step.y)
		info->draw.wall_idx = SO;
	else
		info->draw.wall_idx = NO;
}
