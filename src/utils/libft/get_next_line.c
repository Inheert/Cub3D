/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:23:22 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/05/03 19:16:35 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_fd(int fd, char *start_point_buff)
{
	char	*buffer_readed;
	int		rd_bytes;

	buffer_readed = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer_readed)
		return (NULL);
	rd_bytes = 1;
	buffer_readed[0] = 0;
	while (!ft_strchr_gnl(start_point_buff, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buffer_readed, BUFFER_SIZE);
		if (rd_bytes == -1 || (!rd_bytes && !buffer_readed[0]
				&& (!start_point_buff || !(*start_point_buff))))
		{
			free(buffer_readed);
			free(start_point_buff);
			return (NULL);
		}
		buffer_readed[rd_bytes] = '\0';
		start_point_buff = ft_strjoin_gnl(start_point_buff, buffer_readed);
	}
	free(buffer_readed);
	return (start_point_buff);
}

char	*get_next_line(int fd)
{
	static char	*start_point_buff;
	char		*line_to_w;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	start_point_buff = ft_read_fd(fd, start_point_buff);
	if (!start_point_buff)
		return (NULL);
	line_to_w = ft_get_line(start_point_buff);
	start_point_buff = ft_find_new_start(start_point_buff);
	return (line_to_w);
}
