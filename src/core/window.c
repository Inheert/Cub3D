/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:04:11 by tclaereb          #+#    #+#             */
/*   Updated: 2025/01/22 08:39:11 by tclaereb         ###   ########.fr       */
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

#define mapX  8      //map width
#define mapY  8      //map height
#define mapS 64      //map cube size

int	map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,1,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void draw_map_2d()
{
	int x, y, xo, yo;

	y = -1;
	while (++y < mapY)
	{
		x = -1;
		while (++x < mapX)
		{
			xo = MINIMAP_WIDTH / mapX;
			yo = MINIMAP_HEIGHT / mapY;
			if (map[y * mapX + x] == 1)
				draw_rectangle(TILE_SIZE * x + 1, TILE_SIZE * y + 1, TILE_SIZE - 1, TILE_SIZE - 1, get_hexa_color(200, 200, 200, 255));
			else
				draw_rectangle(TILE_SIZE * x + 1, TILE_SIZE * y + 1, TILE_SIZE - 1, TILE_SIZE - 1, get_hexa_color(15, 15, 15, 255));
		}
	}
}

float px, py, pdx, pdy, pa;

void	cub_keys_hooks(mlx_key_data_t keydata, void *param)
{
	(void)param;
	(void)keydata;
	printf("%d\n", keydata.key);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_window();
	if (keydata.key == MLX_KEY_W)
	{
		px += pdx * PLAYER_SPEED * g_window->delta_time;
		py += pdy * PLAYER_SPEED * g_window->delta_time;
	}
	if (keydata.key == MLX_KEY_S)
	{
		px -= pdx * PLAYER_SPEED * g_window->delta_time;
		py -= pdy * PLAYER_SPEED * g_window->delta_time;
	}
	if (keydata.key == MLX_KEY_A)
	{
		float	strafe_angle = pa -  PI / 2;
		px += cos(strafe_angle) * PLAYER_SPEED * g_window->delta_time;
		py += sin(strafe_angle) * PLAYER_SPEED * g_window->delta_time;
	}
	if (keydata.key == MLX_KEY_D)
	{
		float	strafe_angle = pa + PI / 2;
		px += cos(strafe_angle) * PLAYER_SPEED * g_window->delta_time;
		py += sin(strafe_angle) * PLAYER_SPEED * g_window->delta_time;
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
}

void draw_player_2d()
{
	draw_rectangle( px - MINIMAP_PLAYER_SIZE * 0.5, py - MINIMAP_PLAYER_SIZE * 0.5,
		MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE, get_hexa_color(200, 0, 0, 255));
}

void draw_rays_2d()
{
	float ra, rdx, rdy, ray_x, ray_y;
	int ray_count = 100;
	float fov = PI / 4;
	float angle_step = fov / ray_count;

	ra = pa - (fov / 2);
	while (ra < 0) ra += 2 * PI;
	while (ra > 2 * PI) ra -= 2 * PI;
	// printf("player pos: %d %d\n", (int)(px / TILE_SIZE), (int)(py / TILE_SIZE));
	for (int i = 0; i < ray_count; i++)
	{
		float current_ra = ra;
		ray_x = px;
		ray_y = py;
		rdx = cos(current_ra);
		rdy = sin(current_ra);
		while (1)
		{
			int	ray_cell_x = (int)(ray_x / TILE_SIZE);
			int	ray_cell_y = (int)(ray_y / TILE_SIZE);

			if (ray_cell_x < 0 || ray_cell_y < 0 || ray_cell_x >= mapX || ray_cell_y >= mapY)
				break ;

			if (map[ray_cell_y * mapX + ray_cell_x] == 1)
				break ;
			ray_x += rdx;
			ray_y += rdy;
		}

		draw_line(px, py, ray_x, ray_y, get_hexa_color(100, 100, 255, 255), g_game_container);
		ra += angle_step;
		if (ra > 2 * PI) ra -= 2 * PI;
	}
	draw_line(px, py, px + cos(pa) * 20, py + sin(pa) * 20, get_hexa_color(0, 255, 0, 255), g_game_container);
}

void draw_3d_view()
{
	float ra, rdx, rdy, ray_x, ray_y;
	int ray_count = W_WIDTH;
	float fov = PI / 4;
	float angle_step = fov / ray_count;

	ra = pa - (fov / 2);
	while (ra < 0)
		ra += 2 * PI;
	while (ra > 2 * PI)
		ra -= 2 * PI;

	for (int i = 0; i < ray_count; i++)
	{
		float current_ra = ra;
		ray_x = px;
		ray_y = py;
		rdx = cos(current_ra);
		rdy = sin(current_ra);

		// Parcours du rayon jusqu'à ce qu'il touche un mur
		float distance = 0.0;
		while (1)
		{
			int ray_cell_x = (int)(ray_x / TILE_SIZE);
			int ray_cell_y = (int)(ray_y / TILE_SIZE);

			if (ray_cell_x < 0 || ray_cell_y < 0 || ray_cell_x >= mapX || ray_cell_y >= mapY)
				break;

			if (map[ray_cell_y * mapX + ray_cell_x] == 1)
				break;

			// Avancer le rayon
			ray_x += rdx;
			ray_y += rdy;
			distance += 1.0;
		}

		// Corriger la distorsion
		float corrected_distance = distance * cos(ra - pa);

		// Calculer la hauteur du mur
		int wall_height = (int)(TILE_SIZE * W_HEIGHT / corrected_distance);
		if (wall_height > W_HEIGHT)
			wall_height = W_HEIGHT;

		// Déterminer les positions pour dessiner la colonne
		int wall_top = (W_HEIGHT / 2) - (wall_height / 2);
		int wall_bottom = (W_HEIGHT / 2) + (wall_height / 2);
		// printf("w start: %d\n", i * (W_WIDTH / ray_count));
		// Dessiner le ciel
		draw_line(i * (W_WIDTH / ray_count), 0, i * (W_WIDTH / ray_count), wall_top, get_hexa_color(135, 206, 250, 255), g_game_container);

		// Dessiner le mur
		draw_line(i * (W_WIDTH / ray_count), wall_top, i * (W_WIDTH / ray_count), wall_bottom, get_hexa_color(150, 75, 0, 255), g_game_container);

		// Dessiner le sol
		draw_line(i * (W_WIDTH / ray_count), wall_bottom, i * (W_WIDTH / ray_count), W_HEIGHT, get_hexa_color(169, 169, 169, 255), g_game_container);

		// Avancer l'angle
		ra += angle_step;
		if (ra > 2 * PI) ra -= 2 * PI;
	}
}

void	hook_frame_update(void *param)
{
	int	i;
	int	j;

	(void)param;
	i = -1;
	while (++i < MINIMAP_WIDTH)
	{
		j = -1;
		while (++j < MINIMAP_HEIGHT)
			mlx_put_pixel(g_game_container, i, j, 0x00003366);
	}
	draw_map_2d();
	draw_rays_2d();
	draw_3d_view();
	draw_player_2d();
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
	g_game_container = mlx_new_image(window, W_WIDTH, W_HEIGHT);
	if (!g_game_container)
		raise_error("Error:", "game image container creation failed.", 1, true);
	if (mlx_image_to_window(window, g_game_container, 0, 0) == -1)
		raise_error("Error:", "game image container to window failed.", 1, true);
	px = 500;
	py = 500;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	initialize_hooks(map);
	return (window);
}
