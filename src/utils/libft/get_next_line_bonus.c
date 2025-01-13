/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:11:31 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/16 13:19:52 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_fd(int fd, char *start_point)
{
	char	*buff_rd;
	int		rd_bytes;

	buff_rd = gb_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff_rd)
		return (NULL);
	rd_bytes = 1;
	buff_rd[0] = 0;
	while (!ft_strchr1(start_point, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff_rd, BUFFER_SIZE);
		if (rd_bytes == -1 || (!rd_bytes && !buff_rd[0]
				&& (!start_point || !(*start_point))))
		{
			gb_free(buff_rd);
			gb_free(start_point);
			return (NULL);
		}
		buff_rd[rd_bytes] = '\0';
		start_point = ft_strjoin1(start_point, buff_rd);
	}
	gb_free(buff_rd);
	
	return ( start_point);
}

char	*get_next_line_bonus(int fd)
{
	static char	*start_point[4096];
	char		*line;

	if (fd <= 0 || BUFFER_SIZE <= 0 || fd > 4096)
		return (NULL);
	start_point[fd] = ft_read_fd(fd, start_point[fd]);
	if (!start_point[fd])
		return (NULL);
	line = ft_get_line(start_point[fd]);
	start_point[fd] = ft_new_start_point(start_point[fd]);
	return (line);
}
