/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:22:33 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/02/18 18:31:49 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_xx(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		num /= 16;
		len++;
	}
	return (len);
}

void	ft_write_xx(unsigned int num, const char f)
{
	if (num >= 16)
	{
		ft_write_xx((num / 16), f);
		ft_write_xx((num % 16), f);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (f == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			else if (f == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	ft_print_xx(unsigned int num, const char f)
{
	int	len;

	len = 0;
	if (!num)
		len += write(1, "0", 1);
	else
	{
		ft_write_xx(num, f);
		len = ft_len_xx(num);
	}
	return (len);
}
