/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:40:34 by jodiaz-a          #+#    #+#             */
/*   Updated: 2025/01/27 08:26:14 by tclaereb         ###   ########.fr       */
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
		return (raise_error("Error\n", "read_file: bad use of indetifier.\n", 1, true), NULL);
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
		return (raise_error("Error\n", "read_file: bad use of Colors.\n", 1, true), NULL);
	start = &color[i];
	len = 0;
	while (color[i] && (ft_isalnum(color[i]) || color[i] == ','))
	{
		i++;
		len++;
	}
	if (len > 11)
		return (raise_error("Error\n", "read_file: bad use of Colors.\n", 1, true), NULL);
	// printf("colors: i = %i and len = %i\n", i, len);
	return (ft_substr(start, 0, len));
}

/**
 * Get organize the information in the t_file structure
 */
bool	init_file_info(char *line, t_data *dt)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (dt->fi->no = take_path_info(line), true);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (dt->fi->so = take_path_info(line), true);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (dt->fi->we = take_path_info(line), true);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (dt->fi->ea = take_path_info(line), true);
	else if (ft_strncmp(line, "F", 1) == 0)
		return (dt->fi->f = take_colors(line), true);
	else if (ft_strncmp(line, "C", 1) == 0)
		return (dt->fi->c = take_colors(line), true);
	return (false);
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

	while (1)
	{
		line = get_next_line_bonus(fd);
		line1 = get_next_line_bonus(fd1);
		if (line == NULL || line1 == NULL)
			return (raise_error("Error\n", "read_file: gnl return NULL.\n", 1, true), false);
		if (line && *line && dt->fi->complet <= 6)
		{
			while (*line == ' ' || *line == '\n' || *line == '\t')
				line++;
			if (line && *line && init_file_info(line, dt))
					dt->fi->complet++;
			else if (line && *line && (init_file_info(line, dt)) == false)
				return (raise_error("Error\n", "read_file: init_file_info.\n", 1, true), false);
		}
		else if (line && *line && dt->fi->complet == 7
			&& ft_strchr(line, '1') != NULL)//leack???
			return (read_map(line, line1, fd, fd1, dt), 1);
		if (line)
			gb_free(line);
		if (line1)
			gb_free(line1);
	}
	if (line)
		gb_free(line);
	if (line1)
		gb_free(line1);
	return (0);
}

void	read_file(char *file, t_data *dt)
{
	int		fd;
	int		fd1;

	fd = open(file, O_RDONLY, 777);
	// printf("fd: %i\n", fd);
	fd1 = open(file, O_RDONLY, 777);
	// printf("fd1: %i\n", fd1);
	if (fd < 0 || fd1 < 0)
		return (raise_error("Error\n", "read_file: cannot open the file.\n", 1, true));
	if (verify_format_file(fd, fd1, dt) == false)
		return (raise_error("Error\n", "read_file: file usless.\n", 1, true));
	if (dt->map_verif == NULL)
		return (raise_error("Error\n", "read_file: file usless.\n", 1, true));
	close(fd);
	close(fd1);
}
