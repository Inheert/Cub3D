/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:45:54 by jodiaz-a          #+#    #+#             */
/*   Updated: 2023/11/07 14:24:47 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long int	i;
	int			signe;
	int			numero;

	i = 0;
	signe = 1;
	numero = 0;
	while (nptr[i] != '\0' && ((nptr[i] >= 9 && nptr[i] <= 13)
			|| nptr[i] == 32))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= (-1);
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		numero = (numero * 10) + (nptr[i] - 48);
		i++;
	}
	return (numero * signe);
}
