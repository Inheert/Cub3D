/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:16:46 by jodiaz-a          #+#    #+#             */
/*   Updated: 2023/11/09 17:50:36 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*z;

	i = 0;
	z = (const char *)s;
	while (i < n)
	{
		if ((unsigned char)z[i] == (unsigned char)c)
			return ((char *)&z[i]);
		i++;
	}
	return (NULL);
}
