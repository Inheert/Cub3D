/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:04:41 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/14 10:43:22 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	px, py, pa, pdx, pdy, pa;

void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1) {
		mlx_put_pixel(img, x0, y0, color);

		if (x0 == x1 && y0 == y1) break;

		int e2 = 2 * err;

		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
		err += dx;
			y0 += sy;
		}
	}
}

int	min(int lhs, int rhs)
{
	if (lhs <= rhs)
		return (lhs);
	return (rhs);
}

int max(int lhs, int rhs)
{
	if (lhs >= rhs)
		return (lhs);
	return (rhs);
}

int clamp(int x, int upper, int lower)
{
    return min(upper, max(x, lower));
}

int	mapX = 8;
int	mapY = 8;
int	mapC = 64;
int	mapp[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0 ,0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

void	draw_rays(t_map **map)
{
	int	r, mx, my, mp[2], dof;
	float	rx, ry, ra, xo, yo;

	int	i;

	ra = pa;
	i = -1;
	while (++i < 1)
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
			ry = py;
			dof = 8;
		 }
		 while (dof < 8)
		 {
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp[0] = my * mapX + mx;

			if (mp[0] <  mapX * mapY && mapp[mp[0]] == 1)
				dof = 8;
			else
			{
			rx += xo;
			ry += yo;
			dof++;
			}
			printf("map pos: %d\n", mp[0]);
			//printf("Player pos:%f %f, end trace: %f %f supposed ptr pos: %d %d map pos: %d %d\n", px, py, rx, ry, mx, my, mp[0], (*map)->col_count);
			//printf("%d %d\n", clamp(my, (int)(*map)->line_count, 0), clamp(mx, (int)(*map)->col_count, 0));
		 }
		draw_line(g_game_container, px, py, rx, ry, 0x0066FF33);
	}
	(void)r; (void)mp; (void)map;
}

// void draw_rays(t_map **map)
// {
// 	float ray_x, ray_y;
// 	float ray_angle = pa - (45 / 2.0f);
// 	float ray_dx, ray_dy;
// 	int hit;

// 	for (int ray = 0; ray < W_WIDTH; ray++)
// 	{
// 		ray_x = px;
// 		ray_y = py;
// 		ray_dx = cos(ray_angle * PI / 180.0f);
// 		ray_dy = sin(ray_angle * PI / 180.0f);

// 		hit = 0;
// 		// printf("fpwe\n");
// 		while (!hit)
// 		{
// 			ray_x += ray_dx * 5;
// 			ray_y += ray_dy * 5;

// 			int map_x = (int)ray_x;
// 			int map_y = (int)ray_y;

// 			if (map_y >= 0 && map_y < (int)map[0]->line_count && map_x >= 0 && map_x < (int)map[0]->col_count)
// 			{
// 				if (map[map_y][map_x].slot == '1')
// 					hit = 1;
// 			}
// 			else
// 				hit = 1; // En dehors de la carte
// 		}
// 		int screen_x = (int)(ray_x * 10); // Mise à l'échelle selon votre affichage
// 		int screen_y = (int)(ray_y * 10);
// 		if (px >= 0 && py >= 0 && px < W_WIDTH && py < W_HEIGHT
// 		&& screen_x >= 0 && screen_y >= 0 && screen_x < W_WIDTH && screen_y < W_HEIGHT)
// 			draw_line(g_game_container, px, py, screen_x, screen_y, 0x0066FF33);
// 		printf("%f %f - %d %d\n", px, py, screen_x, screen_y);
// 		ray_angle += 45 / (float)W_WIDTH;
// 	}
// }

void	draw_player()
{
	int	i;
	int	j;

	i = -1;
	while (++i < 8)
	{
		j = -1;
		while(++j < 8)
			mlx_put_pixel(g_game_container, px + i, py + j, 0x006666FF);
	}

	draw_line(g_game_container, px, py, px + pdx * 5, py + pdy * 5, 0x0066FF33);
}

void	player_init()
{
	px = 300;
	py = 300;
	pa = 0;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
}

void	player_set_x(int32_t direction)
{
	px += (-pdy * direction * g_window->delta_time * PLAYER_SPEED);
	py += (pdx * direction * g_window->delta_time * PLAYER_SPEED);
}

void	player_set_y(int32_t direction)
{
	px += (pdx * direction * g_window->delta_time * PLAYER_SPEED);
	py += (pdy * direction * g_window->delta_time * PLAYER_SPEED);
}

void	player_set_angle(float ang)
{
	pa += ang * g_window->delta_time * ANGLE_SPEED;

	if (pa < 0)
		pa += 2 * PI;
	else if (pa > PI * 2)
		pa -= 2 * PI;
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;

}
