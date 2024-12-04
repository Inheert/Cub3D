/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:25:47 by tclaereb          #+#    #+#             */
/*   Updated: 2024/12/04 12:49:49 by tclaereb         ###   ########.fr       */
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


# include "../src/utils/garbage_collector/includes/garbage_collector.h"

# include "../src/utils/libft/libft.h"


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
 * @param validated 1 if all the file_information is validated.
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
	char		*lb;
	char		*lm;
	char		*la;

	bool		valid;

}	t_file;

/**
 *
 */
typedef struct s_data
{
	t_file	*fi;

	char	**map_2d;
	int		p_x;
	int		p_y;

}	t_data;

void	raise_error(char *error, char *details, int exit_code, bool critical);

#endif
