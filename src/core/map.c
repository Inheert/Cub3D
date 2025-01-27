/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:51 by tclaereb          #+#    #+#             */
/*   Updated: 2025/01/27 09:01:00 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rectangle(int32_t x, int32_t y, int width, int height, uint32_t color)
{
	int	i;
	int	j;

	i = -1;
	// printf("Draw rect\n");
	while (++i < height)
	{
		if (i + y < 0)
			continue ;
		// printf("1. %d %d %d %d %d %d\n", i, y, height, W_HEIGHT, i + y, i + y > W_HEIGHT);
		if (i + y > W_HEIGHT)
			return ;
		j = -1;
		while (++j < width)
		{
			//printf("%d %d\n", i, j);
			if (j + x < 0)
				continue ;
			if (j + x > W_WIDTH)
				return ;
			mlx_put_pixel(g_game_container, x + j, y + i, color);
		}
	}
}

void	draw_line(int32_t xstart, int32_t ystart, int32_t xend, int32_t yend, uint32_t color, mlx_image_t *image)
{
	int dx = abs(xend - xstart);
	int dy = abs(yend - ystart);
	int sx = (xstart < xend) ? 1 : -1;
	int sy = (ystart < yend) ? 1 : -1;
	int err = dx - dy;

	if (!image)
		return ;
	while (1)
	{
		if (xstart < 0 || (uint32_t)xstart >= image->width)
			break ;
		if (ystart < 0 || (uint32_t)ystart >= image->height)
			break ;
		mlx_put_pixel(image, xstart, ystart, color);
		if (xstart == xend && ystart == yend)
			break;
		int e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			xstart += sx;
		}
		if (e2 < dx) {
		err += dx;
			ystart += sy;
		}
	}
}

uint32_t	get_hexa_color(unsigned int r, unsigned int g, unsigned int b, unsigned int alpha)
{
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	if (alpha > 255)
		alpha = 255;
	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}
