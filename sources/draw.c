/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:56:52 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 18:22:04 by hyojlee          ###   ########.fr       */
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
		if (info->map.map[vec->map.y][vec->map.x] == '1')
			hit = 1;
	}
	if (vec->side == 0)
		vec->perp_wall_dist = (vec->map.x - vec->pos.x + (1 - vec->step.x) / 2) / vec->rayDir.x;
	else 
		vec->perp_wall_dist = (vec->map.y - vec->pos.y + (1 - vec->step.y) / 2) / vec->rayDir.y; 
}

void	set_draw_info(t_draw *draw, t_vector *vec)
{
	draw->line_hei = (int)(HEI / vec->perp_wall_dist);
	draw->draw_start = (HEI / 2) - (draw->line_hei / 2);
	if (draw->draw_start < 0)
		draw->draw_start = 0;
	draw->draw_end = (HEI / 2) + (draw->line_hei / 2);
	if (draw->draw_end >= HEI)
		draw->draw_end = HEI - 1;
	if (vec->side == 0 && vec->step.x == 1)
		draw->wall_idx = EA;
	else if (vec->side == 0 && vec->step.x == -1)
		draw->wall_idx = WE;
	else if (vec->side == 1 && vec->step.y == 1)
		draw->wall_idx = SO;
	else
		draw->wall_idx = NO;

}

void	draw_line(t_info *info)
{
	set_draw_info(&(info->draw), &(info->vec));
	if (info->vec.side == 0)
		info->draw.wallX = info->vec.pos.y + info->vec.perp_wall_dist * info->vec.rayDir.y;
	else
		info->draw.wallX = info->vec.pos.x + info->vec.perp_wall_dist * info->vec.rayDir.x;
	info->draw.wallX -= floor(info->draw.wallX);
	info->draw.tex.x = (int)(info->draw.wallX * (double)TEX_WID);
	if (info->vec.side == 0 && info->vec.rayDir.x > 0)
		info->draw.tex.x = TEX_WID - info->draw.tex.x - 1;
	if (info->vec.side == 1 && info->vec.rayDir.y < 0)
		info->draw.tex.x = TEX_WID - info->draw.tex.x - 1;
	info->draw.step = 1.0 * TEX_HEI / info->draw.line_hei;
	info->draw.tex_pos = (info->draw.draw_start - (HEI / 2 - info->draw.line_hei / 2)) * info->draw.step;
}

void draw(int x, t_info *info)
{
	int	y;
	char	*dest;
	char	*get;

	y = info->draw.draw_start;
	while (y < info->draw.draw_end)
	{
		info->draw.tex.y = (int)info->draw.tex_pos & (TEX_HEI - 1);
		info->draw.tex_pos += info->draw.step;
		get = info->map.imgs[info->draw.wall_idx].addr + (info->draw.tex.y * info->map.imgs[info->draw.wall_idx].line_len
			+ info->draw.tex.x * info->map.imgs[info->draw.wall_idx].bpp / 8);
		info->draw.color = *(unsigned int *)get;
		dest = info->img.addr + (y * info->img.line_len + x * (info->img.bpp / 8));
		*(unsigned int *)dest = info->draw.color;
		y++;
	}
}

void	set_vector(int x, t_vector *vec)
{
	vec->cameraX = 2 * x / (double)WID - 1;
	vec->rayDir.x = vec->dir.x + vec->plane.x * vec->cameraX;
	vec->rayDir.y = vec->dir.y + vec->plane.y * vec->cameraX;
	vec->map.x = (int)vec->pos.x;
	vec->map.y = (int)vec->pos.y;
	vec->delta_dist.x = fabs(1 / vec->rayDir.x);
	vec->delta_dist.y = fabs(1 / vec->rayDir.y);
}

void	set_step(t_vector *vec)
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

void	dda(t_info *info)
{
	t_vector	*vec;
	int			x;

	x = 0;
	vec = &(info->vec);
	while (x < WID)
	{
		set_vector(x, vec);
		set_step(vec);
		chk_hit(info);
		draw_line(info);
		draw(x, info);
		x++;
	}
}

void	draw_image(t_info *info)
{
	draw_background(info);
	dda(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

