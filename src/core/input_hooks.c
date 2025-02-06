/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:01:50 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/06 09:02:13 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_pos(t_cub *cub, float new_x, float new_y)
{
	int	x_index;
	int	y_index;

	x_index = new_x / TILE_SIZE;
	y_index = new_y / TILE_SIZE;
	if (x_index >= 0 && x_index < cub->mapX
		&& cub->map[(int)cub->player_pos[1] / TILE_SIZE][x_index] != '1')
		cub->player_pos[0] = new_x;
	if (y_index >= 0 && y_index < cub->mapY
		&& cub->map[y_index][(int)cub->player_pos[0] / TILE_SIZE] != '1')
		cub->player_pos[1] = new_y;
}

void	vertical_movement(t_cub *cub)
{
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		next_pos(cub, cub->player_pos[0] + cub->player_pos[2] * PLAYER_SPEED
			* cub->mlx->delta_time, cub->player_pos[1] + cub->player_pos[3]
			* PLAYER_SPEED * cub->mlx->delta_time);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		next_pos(cub, cub->player_pos[0] - cub->player_pos[2] * PLAYER_SPEED
			* cub->mlx->delta_time, cub->player_pos[1] - cub->player_pos[3]
			* PLAYER_SPEED * cub->mlx->delta_time);
}

void	horizontal_movement(t_cub *cub)
{
	float	strafe_angle;

	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
	{
		strafe_angle = cub->player_ang - PI * 0.5;
		next_pos(cub, cub->player_pos[0] + cos(strafe_angle) * PLAYER_SPEED
			* cub->mlx->delta_time, cub->player_pos[1] + sin(strafe_angle)
			* PLAYER_SPEED * cub->mlx->delta_time);
	}
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
	{
		strafe_angle = cub->player_ang + PI * 0.5;
		next_pos(cub, cub->player_pos[0] + cos(strafe_angle) * PLAYER_SPEED
			* cub->mlx->delta_time, cub->player_pos[1] + sin(strafe_angle)
			* PLAYER_SPEED * cub->mlx->delta_time);
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
