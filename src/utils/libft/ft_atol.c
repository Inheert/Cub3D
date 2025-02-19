/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:14:24 by tclaereb          #+#    #+#             */
/*   Updated: 2025/02/19 08:14:27 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *nptr)
{
	long int	i;
	long int	signe;
	long int	numero;

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
