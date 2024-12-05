/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:04:41 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/05 14:36:53 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	px, py, pa, pdx, pdy, pa;

void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1) {
		mlx_put_pixel(img, x0, y0, color);

		if (x0 == x1 && y0 == y1) break;

		int e2 = 2 * err;

		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
		err += dx;
			y0 += sy;
		}
	}
}

void	draw_player()
{
	int	i;
	int	j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while(++j < 8)
			mlx_put_pixel(g_game_container, px + i, py + j, 0x006666FF);
	}

	draw_line(g_game_container, px, py, px + pdx * 5, py + pdy * 5, 0x0066FF33);
}

void	player_init()
{
	px = 300;
	py = 300;
	pa = 0;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
}

void	player_set_x(int32_t direction)
{
	px += (-pdy * direction * g_window->delta_time * PLAYER_SPEED);
	py += (pdx * direction * g_window->delta_time * PLAYER_SPEED);
}

void	player_set_y(int32_t direction)
{
	px += (pdx * direction * g_window->delta_time * PLAYER_SPEED);
	py += (pdy * direction * g_window->delta_time * PLAYER_SPEED);
}

void	player_set_angle(float ang)
{
	pa += ang * g_window->delta_time * ANGLE_SPEED;

	if (pa < 0)
		pa += 2 * PI;
	else if (pa > PI * 2)
		pa -= 2 * PI;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;

	printf("ang: %f\n", pa);
}
