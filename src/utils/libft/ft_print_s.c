/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:49:29 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/02/18 18:31:39 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_s(const char *string)
{
	int	i;

	i = 0;
	if (!string)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else
	{
		while (string[i] != '\0')
		{
			write(1, &string[i], 1);
			i++;
		}
		return (i);
	}
}
