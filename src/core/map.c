/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:25:51 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/14 07:20:14 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_draw_param	create_param_struct(int32_t xstart, int32_t ystart,
	int32_t xend, int32_t yend)
{
	t_draw_param	param;

	param.xstart = xstart;
	param.ystart = ystart;
	param.xend = xend;
	param.yend = yend;
	return (param);
}

uint32_t	get_hexa_color(unsigned int r, unsigned int g, unsigned int b,
	unsigned int alpha)
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

void	draw_rectangle(t_draw_param param, uint32_t color, mlx_image_t *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < param.yend)
	{
		if (i + param.ystart < 0)
			continue ;
		if (i + param.ystart > W_HEIGHT)
			return ;
		j = -1;
		while (++j < param.xend)
		{
			if (j + param.xstart < 0)
				continue ;
			if (j + param.xstart > W_WIDTH)
				return ;
			mlx_put_pixel(img, param.xstart + j, param.ystart + i, color);
		}
	}
}

void	process_draw_line(t_draw_param param, int dx, int dy)
{
	int	err;
	int	e2;

	err = dx - dy;
	while (1)
	{
		if (param.xstart < 0 || (uint32_t)param.xstart >= param.image->width)
			break ;
		if (param.ystart < 0 || (uint32_t)param.ystart >= param.image->height)
			break ;
		mlx_put_pixel(param.image, param.xstart, param.ystart, param.color);
		if (param.xstart == param.xend && param.ystart == param.yend)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			param.xstart += param.sx;
		}
		if (e2 < dx)
		{
			err += dx;
			param.ystart += param.sy;
		}
	}
}

void	draw_line(t_draw_param param, uint32_t color, mlx_image_t *image)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;

	if (!image)
		return ;
	dx = abs(param.xend - param.xstart);
	dy = abs(param.yend - param.ystart);
	sx = -1;
	if (param.xstart < param.xend)
		sx = 1;
	sy = -1;
	if (param.ystart < param.yend)
		sy = 1;
	param.color = color;
	param.image = image;
	param.sx = sx;
	param.sy = sy;
	process_draw_line(param, dx, dy);
}
