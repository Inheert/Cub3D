/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:47 by tclaereb          #+#    #+#             */
/*   Updated: 2025/01/22 07:44:10 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>

# include "../src/utils/libft/libft.h"
# include "../src/utils/garbage_collector/includes/garbage_collector.h"
# include "MLX42/MLX42.h"

# define W_WIDTH 2048
# define W_HEIGHT 1024
# define MINIMAP_WIDTH 1024
# define MINIMAP_HEIGHT 1024
# define MINIMAP_PLAYER_SIZE 30

# define TILE_SIZE 128

# define PLAYER_SPEED 45
# define ANGLE_SPEED 60

# define PI 3.14159265359
# define P2 PI / 2
# define P3 3 * PI / 2

/* **************************--Structures--********************************** */

/**
 * Stock file information for futer use
 *
 * @param no path: north texture.
 * @param so path: south texture.
 * @param we path: west texture.
 * @param ea path: east texture.
 * @param f path: north texture.
 * @param c path: north texture.
 * @param complet number of identifier find in the file.
 *
 * @param nl number of lines.
 * @param nc number of colons.
 *
 * @param line char * to the line before the map.
 * @param lb line before lm (UP).
 * @param lm line for next_line_keep_map_close().
 * @param la line before lm (DWON).
 *
 * @param valid 1 if all the file_information is validated.
 * 					0 if is not.
 *
 */
typedef struct s_file_info
{
	const char	*no;
	const char	*so;
	const char	*we;
	const char	*ea;
	const char	*f;
	const char	*c;
	int			complet;

	int			nl;
	int			nc;

	char		*line;

	bool		valid;

}	t_file;

/**
 *
 */
typedef struct s_data
{
	t_file	*fi;

	// char	**map;
	char	*map_verif;
	int		pos_player;
	// int		p_x;
	// int		p_y;

}	t_data;

typedef enum s_map_build
{
	PLAYER,
	WALL,
	FLOOR,
	EMPTY,
}	t_map_build;

typedef struct s_map
{
	char			slot;
	struct s_map	*up;
	struct s_map	*right;
	struct s_map	*down;
	struct s_map	*left;
	unsigned int	line_count;
	unsigned int	col_count;
}	t_map;

extern mlx_t		*g_window;
extern mlx_image_t	*g_game_container;

void	raise_perror(char *error, bool critical);
void	raise_error(char *error, char *details, int exit_code, bool critical);

void	read_file(char *file, t_data *dt);
bool	read_map(char *line, char *line1, int fd, int fd1, t_data *dt);
int		flood_fill(t_data *dt, int courrent_pos);
mlx_t	*create_window();
void	player_init();
void	draw_player();
void	draw_map(t_map **map);
void	player_set_x(int32_t direction);
void	player_set_y(int32_t direction);
void	player_set_angle(float ang);
void	draw_rays(t_map **map);
void	draw_rectangle(int32_t x, int32_t y, int width, int height, uint32_t color);
void	draw_line(int32_t xstart, int32_t ystart, int32_t xend, int32_t yend, uint32_t color, mlx_image_t *g_game_container);
uint32_t	get_hexa_color(unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

#endif
