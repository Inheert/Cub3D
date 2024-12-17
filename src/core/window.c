/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:04:11 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/14 08:58:02 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_window()
{
	mlx_close_window(g_window);
	mlx_terminate(g_window);
	gb_free_all();
	exit(0);
}

void	cub_keys_hooks(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_window();
	if (keydata.key == MLX_KEY_W)
		player_set_y(1);
	if (keydata.key == MLX_KEY_S)
		player_set_y(-1);
	if (keydata.key == MLX_KEY_A)
		player_set_x(-1);
	if (keydata.key == MLX_KEY_D)
		player_set_x(1);
	if (keydata.key == MLX_KEY_LEFT)
		player_set_angle(-0.1);
	if (keydata.key == MLX_KEY_RIGHT)
		player_set_angle(0.1);
}

void	hook_frame_update(void *param)
{
	int	i;
	int	j;

	i = -1;
	while (++i < W_WIDTH * 0.5)
	{
		j = -1;
		while (++j < W_HEIGHT)
			mlx_put_pixel(g_game_container, i, j, 0x00003366);
	}
	draw_map((t_map **)param);
	draw_player();
	draw_rays((t_map **)param);
}

void	initialize_hooks(t_map **map)
{
	mlx_key_hook(g_window, &cub_keys_hooks, NULL);
	mlx_loop_hook(g_window,  &hook_frame_update, map);
}

mlx_t	*create_window(t_map **map)
{
	mlx_t	*window;

	window = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", false);
	if (!window)
		raise_perror("a problem occur while creating the mlx window.", true);
	g_window = window;
	g_game_container = mlx_new_image(window, W_WIDTH * 0.5, W_HEIGHT);
	if (!g_game_container)
		raise_error("Error:", "game image container creation failed.", 1, true);
	if (mlx_image_to_window(window, g_game_container, 0, 0) == -1)
		raise_error("Error:", "game image container to window failed.", 1, true);
	initialize_hooks(map);
	return (window);
}
