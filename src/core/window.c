/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:04:11 by tclaereb          #+#    #+#             */
/*   Updated: 2025/01/30 12:03:25 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_window(t_cub *cub)
{
	mlx_close_window(cub->mlx);
	mlx_terminate(cub->mlx);
	gb_free_all();
	exit(0);
}

void	real_draw_map_2d(t_cub *cub, int map_x, int map_y, int pos[2])
{
	if (map_x < 0 || map_y < 0 || map_x >= cub->mapX || map_y >= cub->mapY)
		draw_rectangle(pos[0] * MINIMAP_CELL_SIZE + 1,
			pos[1] * MINIMAP_CELL_SIZE + 1, MINIMAP_CELL_SIZE - 1,
			MINIMAP_CELL_SIZE - 1, get_hexa_color(41, 79, 73, 255),
			cub->game_img);
	else if (cub->map[map_y][map_x] == '1')
		draw_rectangle(pos[0] * MINIMAP_CELL_SIZE + 1,
			pos[1] * MINIMAP_CELL_SIZE + 1, MINIMAP_CELL_SIZE - 1,
			MINIMAP_CELL_SIZE - 1, get_hexa_color(129, 120, 145, 255),
			cub->game_img);
	else
		draw_rectangle(pos[0] * MINIMAP_CELL_SIZE + 1,
			pos[1] * MINIMAP_CELL_SIZE + 1, MINIMAP_CELL_SIZE - 1,
			MINIMAP_CELL_SIZE - 1, get_hexa_color(179, 168, 175, 255),
			cub->game_img);
}

void	draw_map_2d(t_cub *cub, int x, int y)
{
	int	cell_count;
	int	start_x;
	int	start_y;
	int	pos[2];

	cell_count = MINIMAP_SIZE / MINIMAP_CELL_SIZE;
	start_x = (int)(cub->player_pos[0] / TILE_SIZE) - cell_count * 0.5;
	start_y = (int)(cub->player_pos[1] / TILE_SIZE) - cell_count * 0.5;
	draw_rectangle(0, 0, MINIMAP_SIZE - cell_count * 0.5,
		MINIMAP_SIZE - cell_count * 0.5, get_hexa_color(42, 42, 42, 255),
		cub->game_img);
	y = -1;
	while (++y < cell_count)
	{
		x = -1;
		while (++x < cell_count)
		{
			pos[0] = x;
			pos[1] = y;
			real_draw_map_2d(cub, start_x + x, start_y + y, pos);
		}
	}
	draw_rectangle(MINIMAP_SIZE * 0.5, MINIMAP_SIZE * 0.5, 15, 15, get_hexa_color(255, 0, 0, 255), cub->game_img);
}

void	next_pos(t_cub *cub, float new_x, float new_y)
{
	int x_index;
	int	y_index;

	x_index = new_x / TILE_SIZE;
	y_index = new_y / TILE_SIZE;

	if (cub->map[(int)cub->player_pos[1] / TILE_SIZE][x_index] != '1')
		cub->player_pos[0] = new_x;
	if (cub->map[y_index][(int)cub->player_pos[0] / TILE_SIZE] != '1')
		cub->player_pos[1]= new_y;
}

void	vertical_movement(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		next_pos(cub, cub->player_pos[0] + cub->player_pos[2] * PLAYER_SPEED * cub->mlx->delta_time,
			cub->player_pos[1] + cub->player_pos[3] * PLAYER_SPEED * cub->mlx->delta_time);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		next_pos(cub, cub->player_pos[0] - cub->player_pos[2] * PLAYER_SPEED * cub->mlx->delta_time,
			cub->player_pos[1] - cub->player_pos[3] * PLAYER_SPEED * cub->mlx->delta_time);
}

void	horizontal_movement(t_cub *cub)
{
	float strafe_angle;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		strafe_angle = cub->player_ang - PI * 0.5;
		next_pos(cub, cub->player_pos[0] + cos(strafe_angle) * PLAYER_SPEED * cub->mlx->delta_time,
			cub->player_pos[1] + sin(strafe_angle) * PLAYER_SPEED * cub->mlx->delta_time);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		strafe_angle = cub->player_ang + PI * 0.5;
		next_pos(cub, cub->player_pos[0] + cos(strafe_angle) * PLAYER_SPEED * cub->mlx->delta_time,
			cub->player_pos[1] + sin(strafe_angle) * PLAYER_SPEED * cub->mlx->delta_time);
	}
}

void	player_rotation(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
	{
		cub->player_ang -= 0.1;
		if (cub->player_ang < 0)
			cub->player_ang += 2 * PI;
		cub->player_pos[2] = cos(cub->player_ang) * 5;
		cub->player_pos[3] = sin(cub->player_ang) * 5;
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
	{
		cub->player_ang += 0.1;
		if (cub->player_ang > 2 * PI)
			cub->player_ang -= 2 * PI;
		cub->player_pos[2] = cos(cub->player_ang) * 5;
		cub->player_pos[3] = sin(cub->player_ang) * 5;
	}
}

void	cub_keys_hooks(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		close_window(cub);
	vertical_movement(cub);
	horizontal_movement(cub);
	player_rotation(cub);
}

void draw_3d_view(t_cub	*cub)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	float	current_ra;
	float	distance;
	int		hit_texture_x;
	float ra, rdx, rdy, ray_x, ray_y;
	int ray_count = W_WIDTH;
	int	ray_cell_x;
	int	ray_cell_y;
	float	rest;
	float	fov = PI / 4;
	float	angle_step = fov / ray_count;
	float	corrected_distance;
	int	wall_height;
	int	wall_top;
	int	wall_bottom;
	int	texture_width;
	int	texture_height;
	int	texture_y;
	int	texture_index;
	int	i;
	int	y;

	mlx_texture_t	*texture;

	ra = cub->player_ang - (fov * 0.5);
	while (ra < 0)
		ra += 2 * PI;
	while (ra > 2 * PI)
		ra -= 2 * PI;
	i = -1;
	while (++i < ray_count)
	{
		current_ra = ra;
		ray_x = cub->player_pos[0];
		ray_y = cub->player_pos[1];
		rdx = cos(current_ra);
		rdy = sin(current_ra);
		distance = 0.0;
		hit_texture_x = 0;
		while (1)
		{
			ray_cell_x = (int)(ray_x / TILE_SIZE);
			ray_cell_y = (int)(ray_y / TILE_SIZE);
			if (ray_cell_x < 0 || ray_cell_y < 0 || ray_cell_x >= cub->mapX || ray_cell_y >= cub->mapY)
				break;

			if (cub->map[ray_cell_y][ray_cell_x] == '1')
			{
				rest = fmodf(ray_y, TILE_SIZE);
				if (rest > TILE_SIZE - 2)
					texture = cub->north_texture;
				else if (rest < 1)
					texture = cub->south_texture;
				else if (ray_x < cub->player_pos[0])
					texture = cub->west_texture;
				else
					texture = cub->east_texture;
				if (rest > TILE_SIZE - 2 || rest < 1)
					hit_texture_x = (int)((fmodf(ray_x, TILE_SIZE) / TILE_SIZE) * texture->width);
				else
					hit_texture_x = (int)((fmodf(ray_y, TILE_SIZE) / TILE_SIZE) * texture->width);
				break;
			}
			ray_x += rdx;
			ray_y += rdy;
			distance += 1.0;
		}
		corrected_distance = distance * cos(ra - cub->player_ang);
		wall_height = (int)(TILE_SIZE * W_HEIGHT / corrected_distance);
		wall_top = (W_HEIGHT * 0.5) - (wall_height * 0.5);
		wall_bottom = (W_HEIGHT * 0.5) + (wall_height * 0.5);
		texture_width = texture->width;
		texture_height = texture->height;
		y = wall_top - 1;
		while (++y < wall_bottom)
		{
			texture_y = (int)(((float)(y - wall_top) / wall_height)
				* texture_height);
			texture_index = (texture_y * texture_width + hit_texture_x) * 4;
			r = texture->pixels[texture_index];
			g = texture->pixels[texture_index + 1];
			b = texture->pixels[texture_index + 2];
			a = texture->pixels[texture_index + 3];
			if (i < 0 || y < 0 || i >= W_WIDTH || y >= W_HEIGHT)
				continue ;
			mlx_put_pixel(cub->game_img, i, y, get_hexa_color(r, g, b, a));
		}
		draw_line(i * (W_WIDTH / ray_count), 0,
			i * (W_WIDTH / ray_count), wall_top,
			get_hexa_color(135, 206, 250, 255), cub->game_img);
		draw_line(i * (W_WIDTH / ray_count),
			wall_bottom, i * (W_WIDTH / ray_count), W_HEIGHT,
			get_hexa_color(169, 169, 169, 255), cub->game_img);
		ra += angle_step;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

void	hook_frame_update(void *param)
{
	draw_3d_view(param);
	draw_map_2d(param, 0, 0);
}

void	initialize_hooks(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, &cub_keys_hooks, cub);
	mlx_loop_hook(cub->mlx, &hook_frame_update, cub);
}

mlx_t	*create_window(t_cub *cub)
{
	int	x;
	int	y;

	cub->mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", false);
	if (!cub->mlx)
		raise_perror("a problem occur while creating the mlx window.", true);
	cub->game_img = mlx_new_image(cub->mlx, W_WIDTH, W_HEIGHT);
	if (!cub->game_img)
		raise_error("Error:", "game image container creation failed.", 1, true);
	if (mlx_image_to_window(cub->mlx, cub->game_img, 0, 0) == -1)
		raise_error("Error:", "game image container to window failed.", 1, true);
	cub->texture = mlx_load_png("./src/resources/decors/256_Marble01.png");
	if (cub->player_orientation == 'E')
		cub->player_ang = 0;
	else if (cub->player_orientation == 'S')
		cub->player_ang = PI * 0.5;
	else if (cub->player_orientation == 'W')
		cub->player_ang = PI;
	else if (cub->player_orientation == 'N')
		cub->player_ang = 3 * PI * 0.5;
	y = -1;
	while (++y < cub->mapY)
	{
		x = -1;
		while (++x < cub->mapX)
		{
			if (cub->map[y][x] == 'N' || cub->map[y][x] == 'S' ||
				cub->map[y][x] == 'E' || cub->map[y][x] == 'W')
			{
				cub->player_pos[0] = x * TILE_SIZE + TILE_SIZE * 0.5;
				cub->player_pos[1] = y * TILE_SIZE + TILE_SIZE * 0.5;
				cub->player_pos[2] = cos(cub->player_ang) * 5;
				cub->player_pos[3] = sin(cub->player_ang) * 5;
				break ;
			}
		}
	}
	initialize_hooks(cub);
	return (cub->mlx);
}
