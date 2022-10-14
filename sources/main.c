/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:32:09 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/14 17:17:28 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_info	info;

	ft_bzero(&(info), sizeof(t_info));
	chk_arg(argc, argv);
	chk_file(&(info.map), argv[1]);
	get_map_arg(&info);
	return (0);
}
