/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:40:34 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/19 09:01:38 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Take the information that the structure t_file
 * is going to keep
 */
char	*take_path_info(char *line)
{
	char	*path;
	char	*png;
	int		i;

	path = ft_strchr(line, '.');
	png = ft_strrchr(line, '.');
	if (path == NULL || png == NULL || (ft_strncmp(png, ".png\n", 5) != 0
			&& ft_strncmp(png, ".png ", 5) != 0))
		return (raise_error("Parsing",
				"read_file: bad use of indetifier.", 1, true), NULL);
	i = 0;
	while (ft_isgraph(path[i]))
		i++;
	return (ft_substr(path, 0, i));
}

int	*take_colors(char *color)
{
	int		*start;
	int		i;
	int		j;

	start = (int *)malloc(sizeof(int) * 3);
	i = 0;
	while (color[i] == 'F' || color[i] == 'C' || color[i] == ' ')
		i++;
	if (!color[i] && !ft_isalnum(color[i]))
		return (raise_error("Parsing",
				"read_file: bad use of Colors.", 1, true), NULL);
	j = 0;
	while (j < 3)
	{
		start[j] = ft_atol(&color[i]);
		while (color[i] && ft_isalnum(color[i]))
			i++;
		if (color[i] == ',')
			i++;
		j++;
	}
	if (color[i] && (color[i] > 33 && color[i] < 127))
		return (raise_error("Parsing",
				"read_file: bad use of Colors.", 1, true), NULL);
	return (start);
}

bool	process_line(char *line, t_data *dt)
{
	while (*line == ' ' || *line == '\n' || *line == '\t')
		line++;
	if (*line && init_file_info(line, dt))
		dt->fi->complet++;
	else if (*line && !init_file_info(line, dt))
		return (raise_error("Parsing",
				"read_file: init_file_info.", 1, true), false);
	return (true);
}

/**
 * tratar el caso cuando se llega al final del file
 *
 * Before going to read_map it verify:
 * 	- there are more lines to read
 * 	- the 6 informations tha must have the file were fulfill
 * 	- we are in the first line with a 1 as first printchar.
 */
bool	verify_format_file(int fd, int fd1, t_data *dt)
{
	char	*line;
	char	*line1;
	int		tfd[2];

	tfd[0] = fd;
	tfd[1] = fd1;
	while (1)
	{
		line = get_next_line_bonus(tfd[0]);
		line1 = get_next_line_bonus(tfd[1]);
		if (!line || !line1)
			return (raise_error("Parsing",
					"read_file: gnl return NULL.", 1, true),
				free_and_return(line, line1, false));
		if (*line && dt->fi->complet <= 6 && !process_line(line, dt))
			return (free_and_return(line, line1, false));
		if (*line && dt->fi->complet == 7 && ft_strchr(line, '1'))
			return (read_map(line, line1, tfd, dt), true);
		free_and_return(line, line1, true);
	}
}

void	read_file(char *file, t_data *dt)
{
	int		fd;
	int		fd1;

	fd = open(file, O_RDONLY, 777);
	fd1 = open(file, O_RDONLY, 777);
	if (fd < 0 || fd1 < 0)
		return (raise_error("Parsing",
				"read_file: cannot open the file.", 1, true));
	if (verify_format_file(fd, fd1, dt) == false)
		return (raise_error("Parsing", "read_file: file usless.", 1, true));
	if (dt->map_verif == NULL)
		return (raise_error("Parsing", "read_file: file usless.", 1, true));
	close(fd);
	close(fd1);
}
