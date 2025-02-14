/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:47 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/14 05:52:45 by tclaereb         ###   ########.fr       */
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
# define W_HEIGHT 2048
# define MINIMAP_SIZE W_WIDTH * 0.2
# define MINIMAP_CELL_SIZE 25
# define MINIMAP_CELL_OFFSET 2
# define MINIMAP_PLAYER_SIZE 30

# define TILE_SIZE 128

# define PLAYER_SPEED 100
# define ANGLE_SPEED 60

# define PI 3.14159265359

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

typedef struct s_data
{
	t_file	*fi;

	char	**map;
	char	*map_verif;
	char	vue_player;
	int		pos_player;
}	t_data;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*game_img;
	mlx_image_t		*minimap_img;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	char			player_orientation;
	float			player_pos[6];
	float			player_ang;
	char			**map;
	int				mapX;
	int				mapY;
}	t_cub;

typedef struct s_raycast
{
	float	current_ra;
	float	distance;
	int		hit_texture_x;
	float ra, rdx, rdy, ray_x, ray_y;
	int	ray_cell_x;
	int	ray_cell_y;
	float	rest;
	float	fov;
	float	angle_step;
	float	corrected_distance;
	int	wall_height;
	int	wall_top;
	int	wall_bottom;
	int	texture_width;
	int	texture_height;
	int	texture_y;
	int	texture_index;
	int	i;
	int	y;
}	t_raycast;

typedef struct s_draw_param
{
	int32_t		xstart;
	int32_t		ystart;
	int32_t		xend;
	int32_t		yend;
	int			sx;
	int			sy;
	uint32_t	color;
	mlx_image_t	*image;
}	t_draw_param;

void	safe_close_mlx(mlx_t *mlx);
void	raise_perror(char *error, bool critical);
void	raise_error(char *error, char *details, int exit_code, bool critical);

void	read_file(char *file, t_data *dt);
bool	read_map(char *line, char *line1, int tfd[2], t_data *dt);
int		flood_fill(t_data *dt, int courrent_pos);

int		ft_is_cub(const char *file);
void	init_t_file(t_file *fi);
void	printing_all_file_info(t_file *fi, t_data *dt);
bool	allocate_map_rows(t_data *dt);
void	fill_map_rows(t_data *dt);
void	str_to_table(t_data *dt);

char	*take_path_info(char *line);
char	*take_colors(char *color);
bool	init_file_info(char *line, t_data *dt);
bool	free_and_return(char *line, char *line1, bool result);
int		is_player(char *p, t_data *dt, int i);
mlx_t		*create_window(t_cub *cub);
void		close_window(t_cub *cub);
void		vertical_movement(t_cub *cub);
void		horizontal_movement(t_cub *cub);
void		player_rotation(t_cub *cub);
void		draw_3d_view(t_cub	*cub);
void		draw_map_2d(t_cub *cub, int x, int y);
t_draw_param	create_param_struct(int32_t xstart, int32_t ystart,
			int32_t xend, int32_t yend);
void		draw_rectangle(t_draw_param param, uint32_t color, mlx_image_t *img);
void		draw_line(t_draw_param param, uint32_t color, mlx_image_t *image);
uint32_t	get_hexa_color(unsigned int r, unsigned int g, unsigned int b, unsigned int alpha);

#endif
