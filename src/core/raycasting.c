/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 08:57:20 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/14 05:47:47 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_good_texture(t_cub *cub, t_raycast *va, mlx_texture_t **texture)
{
	int	ray_y_rest;
	int	ray_x_rest;

	ray_y_rest = (int)va->ray_y % TILE_SIZE;
	ray_x_rest = (int)va->ray_x % TILE_SIZE;
	if ((ray_x_rest == 0 || ray_x_rest == 127) && (ray_y_rest == 0 || ray_y_rest == 127) && texture && *texture)
		return ;
	if (ray_y_rest == TILE_SIZE - 1)
		*texture = cub->north_texture;
	else if (ray_y_rest == 0)
		*texture = cub->south_texture;
	else if (ray_x_rest == TILE_SIZE - 1)
		*texture = cub->west_texture;
	else
		*texture = cub->east_texture;
}

void	proceeds_raycasting(t_cub *cub, t_raycast *va, mlx_texture_t **texture)
{
	while (1)
	{
		va->ray_cell_x = (int)(va->ray_x / TILE_SIZE);
		va->ray_cell_y = (int)(va->ray_y / TILE_SIZE);
		if (va->ray_cell_x < 0 || va->ray_cell_y < 0
			|| va->ray_cell_x >= cub->mapX || va->ray_cell_y >= cub->mapY)
			break ;
		if (cub->map[va->ray_cell_y][va->ray_cell_x] == '1')
		{
			va->rest = fmodf(va->ray_y, TILE_SIZE);
			float x_offset = fmodf(va->ray_x, TILE_SIZE);
			float y_offset = fmodf(va->ray_y, TILE_SIZE);

			set_good_texture(cub, va, texture);
			if (x_offset < 1 || x_offset > TILE_SIZE - 1)
				va->hit_texture_x = (int)((y_offset / TILE_SIZE) * (*texture)->width);
			else
				va->hit_texture_x = (int)((x_offset / TILE_SIZE) * (*texture)->width);
			break ;
		}
		va->ray_x += va->rdx;
		va->ray_y += va->rdy;
		va->distance += 1.0;
	}
}

void	prepare_and_proceed_raycasting(t_cub *cub, t_raycast *va,
	mlx_texture_t **texture)
{
	va->current_ra = va->ra;
	va->ray_x = cub->player_pos[0];
	va->ray_y = cub->player_pos[1];
	va->rdx = cos(va->current_ra);
	va->rdy = sin(va->current_ra);
	va->distance = 0.0;
	va->hit_texture_x = 0;
	proceeds_raycasting(cub, va, texture);
	va->corrected_distance = va->distance * cos(va->ra - cub->player_ang);
	va->wall_height = (int)(TILE_SIZE * W_HEIGHT / va->corrected_distance);
	if (va->wall_height > 15000)
		va->wall_height = 15000;
	va->wall_top = (W_HEIGHT * 0.5) - (va->wall_height * 0.5);
	va->wall_bottom = (W_HEIGHT * 0.5) + (va->wall_height * 0.5);
	va->texture_width = (*texture)->width;
	va->texture_height = (*texture)->height;
	va->y = va->wall_top - 1;
}

void	draw_texture(t_cub *cub, t_raycast *va, mlx_texture_t *texture)
{
	while (++va->y < va->wall_bottom)
	{
		va->texture_y = (int)(((float)(va->y - va->wall_top) / va->wall_height)
				* va->texture_height);
		va->texture_index = (va->texture_y * va->texture_width
				+ va->hit_texture_x) * 4;
		if (va->i < 0 || va->y < 0 || va->i >= W_WIDTH || va->y >= W_HEIGHT)
			continue ;
		mlx_put_pixel(cub->game_img, va->i, va->y,
			get_hexa_color(texture->pixels[va->texture_index],
				texture->pixels[va->texture_index + 1],
				texture->pixels[va->texture_index + 2],
				texture->pixels[va->texture_index + 3]));
	}
}

void	draw_3d_view(t_cub	*cub)
{
	t_raycast		va;
	mlx_texture_t	*texture;

	va.fov = PI / 4;
	va.angle_step = va.fov / W_WIDTH;
	va.ra = cub->player_ang - (va.fov * 0.5);
	while (va.ra < 0)
		va.ra += 2 * PI;
	while (va.ra > 2 * PI)
		va.ra -= 2 * PI;
	va.i = -1;
	texture = NULL;
	while (++va.i < W_WIDTH)
	{
		prepare_and_proceed_raycasting(cub, &va, &texture);
		draw_texture(cub, &va, texture);
		draw_line(create_param_struct(va.i, 0, va.i, va.wall_top),
			get_hexa_color(135, 206, 250, 255), cub->game_img);
		draw_line(create_param_struct(va.i, va.wall_bottom, va.i, W_HEIGHT),
			get_hexa_color(169, 169, 169, 255), cub->game_img);
		va.ra += va.angle_step;
		if (va.ra > 2 * PI)
			va.ra -= 2 * PI;
	}
}
