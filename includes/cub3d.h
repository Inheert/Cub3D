/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:47 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/03 17:52:51 by jodiaz-a         ###   ########.fr       */
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

	char	**map;
	char	*map_verif;
	char	vue_player;
	int		pos_player;
}	t_data;

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

#endif
