/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:40:34 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/02/03 17:48:08 by jodiaz-a         ###   ########.fr       */
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
	int		i;

	path = ft_strchr(line, '.');
	if (path == NULL)
		return (raise_error("Error\n",
				"read_file: bad use of indetifier.\n", 1, true), NULL);
	i = 0;
	while (ft_isgraph(path[i]))
		i++;
	return (ft_substr(path, 0, i));
}

char	*take_colors(char *color)
{
	char	*start;
	int		i;
	int		len;

	i = 0;
	while (color[i] == 'F' || color[i] == 'C' || color[i] == ' ')
		i++;
	if (!color[i] && !ft_isalnum(color[i]))
		return (raise_error("Error\n",
				"read_file: bad use of Colors.\n", 1, true), NULL);
	start = &color[i];
	len = 0;
	while (color[i] && (ft_isalnum(color[i]) || color[i] == ','))
	{
		i++;
		len++;
	}
	if (len > 11)
		return (raise_error("Error\n",
				"read_file: bad use of Colors.\n", 1, true), NULL);
	return (ft_substr(start, 0, len));
}

bool	process_line(char *line, t_data *dt)
{
	while (*line == ' ' || *line == '\n' || *line == '\t')
		line++;
	if (*line && init_file_info(line, dt))
		dt->fi->complet++;
	else if (*line && !init_file_info(line, dt))
		return (raise_error("Error\n",
				"read_file: init_file_info.\n", 1, true), false);
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
			return (raise_error("Error\n",
					"read_file: gnl return NULL.\n", 1, true),
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
		return (raise_error("Error\n",
				"read_file: cannot open the file.\n", 1, true));
	if (verify_format_file(fd, fd1, dt) == false)
		return (raise_error("Error\n", "read_file: file usless.\n", 1, true));
	if (dt->map_verif == NULL)
		return (raise_error("Error\n", "read_file: file usless.\n", 1, true));
	close(fd);
	close(fd1);
}
