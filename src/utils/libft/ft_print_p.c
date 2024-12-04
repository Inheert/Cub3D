/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:52:12 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/02/18 18:31:35 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_p(unsigned long long int num)
{
	int	len_p;

	len_p = 0;
	while (num != 0)
	{
		num /= 16;
		len_p++;
	}
	return (len_p);
}

void	ft_write_p(unsigned long long int num)
{
	if (num >= 16)
	{
		ft_write_p(num / 16);
		ft_write_p(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	ft_print_p( unsigned long long int num)
{
	int	len;

	len = 0;
	len += write(1, "0x", 2);
	if (!num)
		len += write(1, "0", 1);
	else
	{
		ft_write_p(num);
		len += ft_len_p(num);
	}
	return (len);
}
