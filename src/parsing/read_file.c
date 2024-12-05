/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:40:34 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/04 17:52:09 by jodiaz-a         ###   ########.fr       */
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
		return (perror("Error: read_file: bad use of indetifier.\n"), NULL);
	while (ft_isprint(path[i]) && path[i] != ' ')
		i++;
	return (ft_substr(path, 0, i));
}
/**
 * Get organize the information in the t_file structure
 */
char	*init_file_info(char *line, t_data *dt)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (dt->fi->no = take_path_info(line), dt->fi->no);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (dt->fi->so = take_path_info(line), dt->fi->so);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (dt->fi->we = take_path_info(line), dt->fi->we);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (dt->fi->ea = take_path_info(line), dt->fi->ea);
	else if (ft_strncmp(line, "F", 1) == 0)
		return (dt->fi->f = take_path_info(line), dt->fi->f);
	else if (ft_strncmp(line, "C", 1) == 0)
		return (dt->fi->c = take_path_info(line), dt->fi->c);
	return (NULL);
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
	int		spaces;

	while (1)
	{
		line = get_next_line_bonus(fd);
		line1 = get_next_line_bonus(fd1);
		if (line == NULL || line1 == NULL)
			return (perror("Error: read_file: get_next_line return NULL.\n"),
				false);
		spaces = 0;
		if (line && *line && dt->fi->complet != 6)
		{
			while (*line == ' ' || *line++ == '\t')
				spaces++;
			if (line && *line)
				if (init_file_info(line, dt))
					dt->fi->complet++;
		}
		else if (line && *line && dt->fi->complet == 6
			&& ft_strchr(line, '1') != NULL)//leack???
			return (dt->map = read_map(line, line1, fd, fd1, dt), 1);
	}
	return (0);
}

void	read_file(char *file, t_data *dt)
{
	int		fd;
	int		fd1;

	fd = open(file, O_RDONLY, 777);
	fd1 = open(file, O_RDONLY, 777);
	if (fd < 0 || fd1 < 0)
		return (perror("Error: read_file: File cannot be open.\n"));
	if (verify_format_file(fd, fd1, dt) == false)
		return (perror("Error: read_file: File cannot read.\n"));
	if (dt->map == NULL)
		return (perror("Error: read_map: NULL.\n"));
	if (dt->map == NULL)
		return ;
}
