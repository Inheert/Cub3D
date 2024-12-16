/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:12:39 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/16 13:20:28 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen1(char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr1(char *start_point, int bn)
{
	int	i;

	i = 0;
	if (!start_point)
		return (NULL);
	while (start_point[i] != '\0')
	{
		if (start_point[i] == (char )bn)
			return ((char *)&start_point[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin1(char *start_point, char *buffer_rd)
{
	int		i;
	int		j;
	char	*str;

	if (!start_point)
	{
		start_point = gb_malloc(sizeof(char) * 1);
		start_point[0] = '\0';
	}
	if ((!start_point || !buffer_rd))
		return (NULL);
	str = gb_malloc(sizeof(char)
			* (ft_strlen1(start_point) + ft_strlen1(buffer_rd) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (start_point)
		while (start_point[++i] != '\0')
			str[i] = start_point[i];
	while (buffer_rd[j] != '\0')
		str[i++] = buffer_rd[j++];
	str[i] = '\0';
	gb_free(start_point);
	return (str);
}

char	*ft_get_line(char *start_point)
{
	int		len;
	char	*line_to_w;

	len = 0;
	if (!start_point)
		return (NULL);
	while (start_point[len] && start_point[len] != '\n')
		len++;
	line_to_w = gb_malloc(sizeof(char) * (len + 2));
	if (!line_to_w)
		return (NULL);
	len = 0;
	while (start_point[len] && start_point[len] != '\n')
	{
		line_to_w[len] = start_point[len];
		len++;
	}
	if (start_point[len] == '\n')
	{
		line_to_w[len] = start_point[len];
		len++;
	}
	line_to_w[len] = '\0';
	return (line_to_w);
}

char	*ft_new_start_point(char *start_point)
{
	char	*new_start;
	int		i;
	int		j;

	i = 0;
	while (start_point[i] && start_point[i] != '\n')
		i++;
	if (!start_point[i])
	{
		gb_free(start_point);
		return (NULL);
	}
	new_start = gb_malloc(sizeof(char) * (ft_strlen1(start_point) - i + 1));
	if (!new_start)
		return (NULL);
	i++;
	j = 0;
	while (start_point[i])
		new_start[j++] = start_point[i++];
	new_start[j] = '\0';
	gb_free (start_point);
	return (new_start);
}
