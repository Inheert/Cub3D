/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:24:26 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/05/03 19:16:25 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr_gnl(char *start_point_buff, int bn)
{
	int	i;

	i = 0;
	if (!start_point_buff)
		return (NULL);
	while (start_point_buff[i] != '\0')
	{
		if (start_point_buff[i] == (char )bn)
			return ((char *)&start_point_buff[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char *start_point_buff, char *buffer_readed)
{
	int		i;
	int		j;
	char	*str;

	if (!start_point_buff)
	{
		start_point_buff = malloc(sizeof(char) * 1);
		start_point_buff[0] = '\0';
	}
	if ((!start_point_buff || !buffer_readed))
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen_gnl(start_point_buff)
				+ ft_strlen_gnl(buffer_readed) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (start_point_buff)
		while (start_point_buff[++i] != '\0')
			str[i] = start_point_buff[i];
	while (buffer_readed[j] != '\0')
		str[i++] = buffer_readed[j++];
	str[i] = '\0';
	free(start_point_buff);
	return (str);
}

char	*ft_get_line(char *start_point_buff)
{
	int		len;
	char	*line_to_w;

	len = 0;
	if (!start_point_buff)
		return (NULL);
	while (start_point_buff[len] && start_point_buff[len] != '\n')
		len++;
	line_to_w = malloc(sizeof(char) * (len + 2));
	if (!line_to_w)
		return (NULL);
	len = 0;
	while (start_point_buff[len] && start_point_buff[len] != '\n')
	{
		line_to_w[len] = start_point_buff[len];
		len++;
	}
	if (start_point_buff[len] == '\n')
	{
		line_to_w[len] = start_point_buff[len];
		len++;
	}
	line_to_w[len] = '\0';
	return (line_to_w);
}

char	*ft_find_new_start(char *start_point_buff)
{
	char	*new_start;
	int		i;
	int		j;

	i = 0;
	while (start_point_buff[i] && start_point_buff[i] != '\n')
		i++;
	if (!start_point_buff[i])
	{
		free(start_point_buff);
		return (NULL);
	}
	new_start = malloc(sizeof(char)
			* (ft_strlen_gnl(start_point_buff) - i + 1));
	if (!new_start)
		return (NULL);
	i++;
	j = 0;
	while (start_point_buff[i])
		new_start[j++] = start_point_buff[i++];
	new_start[j] = '\0';
	free (start_point_buff);
	return (new_start);
}
