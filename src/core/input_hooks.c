/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:01:50 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/14 06:05:51 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	next_pos(t_cub *cub, float new_x, float new_y)
{
	int	left_x;
	int	right_x;
	int	top_y;
	int	bottom_y;

	left_x = (new_x - PLAYER_WIDTH / 2) / TILE_SIZE;
	right_x = (new_x + PLAYER_WIDTH / 2) / TILE_SIZE;
	top_y = (new_y - PLAYER_WIDTH / 2) / TILE_SIZE;
	bottom_y = (new_y + PLAYER_WIDTH / 2) / TILE_SIZE;
	if (left_x >= 0 && right_x < cub->map_x
		&& cub->map[(int)cub->player_pos[1] / TILE_SIZE][left_x] != '1'
		&& cub->map[(int)cub->player_pos[1] / TILE_SIZE][right_x] != '1')
	{
		cub->player_pos[0] = new_x;
	}
	if (top_y >= 0 && bottom_y < cub->map_y
		&& cub->map[top_y][(int)cub->player_pos[0] / TILE_SIZE] != '1'
		&& cub->map[bottom_y][(int)cub->player_pos[0] / TILE_SIZE] != '1')
	{
		cub->player_pos[1] = new_y;
	}
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
