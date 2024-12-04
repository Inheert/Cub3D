/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:05:30 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/02/18 18:31:41 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_u_len(unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;
	int		len;

	len = ft_u_len(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- && n != 0)
	{
		str[len] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}

int	ft_print_u(unsigned int num)
{
	int		len;
	char	*mem_to_free;

	len = 0;
	if (num == 0)
		len += write(1, "0", 1);
	else
	{
		mem_to_free = ft_uitoa(num);
		len = ft_print_s(mem_to_free);
		free(mem_to_free);
	}
	return (len);
}
