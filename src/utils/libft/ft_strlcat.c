/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:04:26 by jodiaz-a          #+#    #+#             */
/*   Updated: 2023/11/10 13:39:02 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	j = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (n <= len_dst)
		return (n + len_src);
	while (len_dst + i < n - 1 && src[j] != '\0')
	{
		dst[len_dst + i] = src[j];
		j++;
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
