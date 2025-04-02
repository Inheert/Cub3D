/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:26:24 by tclaereb          #+#    #+#             */
/*   Updated: 2025/03/31 17:37:05 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap_texture_pixels_horizontal(mlx_texture_t *texture)
{
	unsigned int	row_size;
	unsigned int	row;
	unsigned int	col;
	int				comp;
	int				temp;

	row_size = texture->width * 4;
	row = -1;
	while (++row < texture->height)
	{
		col = -1;
		while (++col < texture->width * 0.5)
		{
			comp = -1;
			while (++comp < 4)
			{
				temp = texture->pixels[row * row_size + col * 4 + comp];
				texture->pixels[row * row_size + col * 4
					+ comp] = texture->pixels[row * row_size
					+ (texture->width - col - 1) * 4 + comp];
				texture->pixels[row * row_size + (texture->width
						- col - 1) * 4 + comp] = temp;
			}
		}
	}
}

void	load_texture(t_cub *cub, t_file *file_info)
{
	mlx_texture_t	*buff;

	buff = mlx_load_png(file_info->no);
	if (!buff)
		raise_perror("A problem occur while loading North texture.", 1);
	cub->north_texture = buff;
	buff = mlx_load_png(file_info->so);
	if (!buff)
		raise_perror("A problem occur while loading South texture.", 1);
	cub->south_texture = buff;
	swap_texture_pixels_horizontal(cub->south_texture);
	buff = mlx_load_png(file_info->we);
	if (!buff)
		raise_perror("A problem occur while loading West texture.", 1);
	cub->west_texture = buff;
	swap_texture_pixels_horizontal(cub->west_texture);
	buff = mlx_load_png(file_info->ea);
	if (!buff)
		raise_perror("A problem occur while loading East texture.", 1);
	cub->east_texture = buff;
}

int	main(int ac, char **av)
{
	t_data	dt;
	t_file	file_info;
	t_cub	*cub;
	mlx_t	*window;

	if (ac != 2 || !av || !av[1] || !ft_is_cub((const char *)av[1]))
		raise_error("Parsing", "file inexistent or wrong file.", 1, 1);
	init_t_file(&file_info);
	dt.map_verif = NULL;
	dt.fi = &file_info;
	read_file(av[1], &dt);
	str_to_table(&dt);
	cub = gb_malloc(sizeof(t_cub));
	cub->player_orientation = dt.vue_player;
	cub->map = dt.map;
	cub->map_x = dt.fi->nc;
	cub->map_y = dt.fi->nl;
	cub->floor_color = dt.fi->f;
	cub->ceiling_color = dt.fi->c;
	cub->unfocus = false;
	load_texture(cub, &file_info);
	window = create_window(cub);
	mlx_loop(window);
	mlx_terminate(window);
}
