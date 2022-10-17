/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:32:09 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/17 15:08:16 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	leaks(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_info	info;

	ft_bzero(&(info), sizeof(t_info));
	info.map.floor.rgb = -1;
	info.map.ceiling.rgb = -1;
	info.mlx = mlx_init();
	chk_arg(argc, argv);
	chk_file(&(info.map), argv[1]);
	get_map_arg(&info);
	save_map_to_list(&info);
	find_map_size(&(info.map));
	save_map(&(info.map));
	chk_valid_map(&info);
	printf("pos x: %d, pos y: %d\n", info.pos.x, info.pos.y);
	close(info.map.fd);
	// atexit(leaks);
	return (0);
}
