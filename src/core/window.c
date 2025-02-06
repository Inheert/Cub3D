/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:04:11 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/06 09:03:30 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	set_player_pos(t_cub *cub)
{
	int	y;
	int	x;

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
}

mlx_t	*create_window(t_cub *cub)
{
	cub->mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", false);
	if (!cub->mlx)
		raise_perror("a problem occur while creating the mlx window.", true);
	safe_close_mlx(cub->mlx);
	cub->game_img = mlx_new_image(cub->mlx, W_WIDTH, W_HEIGHT);
	if (!cub->game_img)
		raise_error("Error:", "game image creation failed.", 1, true);
	if (mlx_image_to_window(cub->mlx, cub->game_img, 0, 0) == -1)
		raise_error("Error:", "game image to window failed.", 1, true);
	cub->texture = mlx_load_png("./src/resources/decors/256_Marble01.png");
	if (cub->player_orientation == 'E')
		cub->player_ang = 0;
	else if (cub->player_orientation == 'S')
		cub->player_ang = PI * 0.5;
	else if (cub->player_orientation == 'W')
		cub->player_ang = PI;
	else if (cub->player_orientation == 'N')
		cub->player_ang = 3 * PI * 0.5;
	set_player_pos(cub);
	initialize_hooks(cub);
	return (cub->mlx);
}
