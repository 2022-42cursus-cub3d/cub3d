/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:14:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/10/25 13:07:57 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./test.h"

void leaks(void)
{
	system("leaks test");
}

t_data *data(void) {
	static t_data data;

	return (&data);
}

void my_mlx_pixel_put(int x, int y, int color)
{
	char *dest;
	
	while (x < 1920)
	{
		y = 10;
		while (y < 540)
		{
			dest = data()->addr + (y++ * data()->line_len + x * (data()->bpp / 8));
			*(unsigned int*)dest = color;
			y = 540;
		}
		while (y < 1080)
		{
			dest = data()->addr + (y++ * data()->line_len + x * (data()->bpp / 8));
			*(unsigned int*)dest = 0x00FFFFFF;
			
		}
		x++;
	}
}

int game_over(void)
{
	// mlx_destroy_image(data()->mlx, data()->img); // 없어도 누수 발생하지 않음
	mlx_destroy_window(data()->mlx, data()->win); // 없어도 누수 발생하지 않음
	// atexit(leaks);
	exit(0);
	return (0);
}

int key_press(int keycode)
{
	if (keycode == KEY_ESC)
		game_over();
	return (0);
}

int main(void) {
	// data()->mlx = mlx_init();
	// data()->win = mlx_new_window(data()->mlx, 1920, 1080, "Hello world!");
	// data()->img = mlx_new_image(data()->mlx, 1920, 1080);
	// data()->addr = mlx_get_data_addr(data()->img, &(data()->bpp), &(data()->line_len), &(data()->endian));
	// my_mlx_pixel_put(0, 0, 0x00FFFF30);
	// mlx_put_image_to_window(data()->mlx, data()->win, data()->img, 0, 0);
	// mlx_hook(data()->win, X_EVENT_KEY_EXIT, 0, &game_over, 0);
	// mlx_hook(data()->win, X_EVENT_KEY_PRESS, 0, &key_press, 0);
	// mlx_loop(data()->mlx);
	t_rgb rgb;

	rgb.rgbs.blank = 0;
	rgb.rgbs.red = 220;
	rgb.rgbs.green = 200;
	rgb.rgbs.blue = 200;
	printf("%d\n%d\n", rgb.rgb, (220 << 16) + (200 << 8) + 200);
	return (0);
}