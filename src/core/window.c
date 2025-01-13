/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:04:11 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/05 14:36:38 by tclaereb         ###   ########.fr       */
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

	(void)param;
	i = -1;
	while (++i < 1024)
	{
		j = -1;
		while (++j < 1024)
			mlx_put_pixel(g_game_container, i, j, 0x00003366);
	}
	draw_player();
}

void	initialize_hooks()
{
	mlx_key_hook(g_window, &cub_keys_hooks, NULL);
	mlx_loop_hook(g_window,  &hook_frame_update, NULL);
}

mlx_t	*create_window()
{
	mlx_t	*window;

	window = mlx_init(2048, 1024, "Cub3D", false);
	if (!window)
		raise_perror("a problem occur while creating the mlx window.", true);
	g_window = window;
	g_game_container = mlx_new_image(window, 1024, 1024);
	if (!g_game_container)
		raise_error("Error:", "game image container creation failed.", 1, true);
	if (mlx_image_to_window(window, g_game_container, 0, 0) == -1)
		raise_error("Error:", "game image container to window failed.", 1, true);
	initialize_hooks();
	return (window);
}
