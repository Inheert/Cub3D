/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:33:43 by jodiaz-a          #+#    #+#             */
/*   Updated: 2023/11/10 13:52:52 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*z1;
	const char	*z2;

	i = 0;
	z1 = (const char *)s1;
	z2 = (const char *)s2;
	while (i < n)
	{
		if (z1[i] != z2[i])
			return ((unsigned char)z1[i] - (unsigned char)z2[i]);
		i++;
	}
	return (0);
}
