/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:04:11 by tclaereb          #+#    #+#             */
/*   Updated: 2025/01/14 09:59:51 by tclaereb         ###   ########.fr       */
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
				draw_rectangle(xo * x + 1, yo * y + 1, xo - 1, yo - 1, get_hexa_color(200, 200, 200, 255));
			else
				draw_rectangle(xo * x + 1, yo * y + 1, xo - 1, yo - 1, get_hexa_color(15, 15, 15, 255));
		}
	}
}

float px, py, pdx, pdy, pa;

void	cub_keys_hooks(mlx_key_data_t keydata, void *param)
{
	(void)param;
	(void)keydata;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		close_window();
	if (keydata.key == MLX_KEY_W)
	{
		px += pdx;
		py += pdy;
	}
	if (keydata.key == MLX_KEY_S)
	{
		px -= pdx;
		py -= pdy;
	}
	if (keydata.key == MLX_KEY_A)
	{
		pa -= 0.1;
		if (pa < 0)
			pa += 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keydata.key == MLX_KEY_D)
	{
		pa += 0.1;
		if (pa > 2 * PI)
			pa -= 2 * PI;
		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	// if (keydata.key == MLX_KEY_LEFT)
	// 	player_set_angle(-0.1);
	// if (keydata.key == MLX_KEY_RIGHT)
	// 	player_set_angle(0.1);
}

void draw_player()
{
	draw_rectangle( px - MINIMAP_PLAYER_SIZE * 0.5, py - MINIMAP_PLAYER_SIZE * 0.5,
		MINIMAP_PLAYER_SIZE, MINIMAP_PLAYER_SIZE, get_hexa_color(200, 0, 0, 255));
	draw_line(px, py, px + pdx * 5, py + pdy * 5, get_hexa_color(0, 255, 0, 255));
}

void draw_rays_2d()
{
	printf("angle: %f\n", pa);
	int	r, mx, my, mp, dof;
	float	rx, ry, ra, xo, yo;

	ra = pa;
	for (r = 0; r < 1; r++)
	{
		dof = 0;
		float aTan = -1 / tan(ra);
		if (ra > PI)
		{
			ry = (((int)py >> 6) << 6) - 0.0001;
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)py >> 6) << 6) + 64;
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry= py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * mapX + mx;
			if (mp < mapY && map[mp] == 1)
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		// dof = 0;
		// float nTan = -tan(ra);
		// if (ra > P2 && ra < P3)
		// {
		// 	rx = (((int)px >> 6) << 6) - 0.0001;
		// 	ry = (px - rx) * nTan + py;
		// 	xo = -64;
		// 	yo = -xo * nTan;
		// }
		// if (ra < P2 || ra > P3)
		// {
		// 	rx = (((int)px >> 6) << 6) + 64;
		// 	ry = (px - rx) * nTan + py;
		// 	xo = 64;
		// 	yo = -xo * nTan;
		// }
		// if (ra == 0 || ra == PI)
		// {
		// 	rx = px;
		// 	ry = py;
		// 	dof = 8;
		// }
		// while (dof < 8)
		// {
		// 	mx = (int)(rx) >> 6;
		// 	my = (int)(ry) >> 6;
		// 	mp = my * mapX + mx;
		// 	if  (mp < mapX * mapY && map[mp] == 1)
		// 		dof = 8;
		// 	else
		// 	{
		// 		rx += xo;
		// 		ry += yo;
		// 		dof += 1;
		// 	}
		// }
		draw_line(px, py, rx, ry, get_hexa_color(0, 255, 255, 255));
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
	draw_player();
	draw_rays_2d();
	// draw_map((t_map **)param);
	// draw_player();
	// draw_rays((t_map **)param);
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
	px = 500;
	py = 500;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	initialize_hooks(map);
	return (window);
}
