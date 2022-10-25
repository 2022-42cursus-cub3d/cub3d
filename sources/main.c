/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:32:09 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 13:32:49 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	leaks(void)
{
	system("leaks cub3D");
}

void	init_mlx(t_info *info)
{
	info->win = mlx_new_window(info->mlx, WID, HEI, "cub3d");
	info->img.img = mlx_new_image(info->mlx, WID, HEI);
	info->img.addr = mlx_get_data_addr(info->img.img, &(info->img.bpp)
		, &(info->img.line_len), &(info->img.endian));
	mlx_hook(info->win, X_EVENT_KEY_PRESS, 0, key_press, info);
	mlx_hook(info->win, X_EVENT_KEY_RELEASE, 0, key_release, info);
	mlx_hook(info->win, X_EVENT_KEY_EXIT, 0, terminate, info);
	mlx_loop_hook(info->mlx, game_loop, info);
	mlx_loop(info->mlx);
}

int	main(int argc, char **argv)
{
	t_info	info;

	ft_bzero(&(info), sizeof(t_info));
	info.map.floor.rgb = -1;
	info.map.ceiling.rgb = -1;
	chk_arg(argc, argv);
	chk_file(&(info.map), argv[1]);
	info.mlx = mlx_init(); // save_img 함수에서 mlx 포인터가 필요함
	get_map_arg(&info);
	save_map_to_list(&info);
	find_map_size(&(info.map));
	save_map(&(info.map));
	chk_valid_map(&info);
	decide_dir(&info);
	printf("pos x: %lf, pos y: %lf\n", info.vec.pos.x, info.vec.pos.y);
	init_mlx(&info);
	close(info.map.fd);
	// atexit(leaks);
	return (0);
}
