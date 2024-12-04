/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:11:43 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/02/18 18:31:52 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_datatype(const char f, va_list args)
{
	int	len;

	len = 0;
	if (f == 'c')
		len += ft_print_c(va_arg(args, int));
	else if (f == 's')
		len += ft_print_s(va_arg(args, const char *));
	else if (f == 'p')
		len += ft_print_p(va_arg(args, unsigned long long int));
	else if (f == 'd' || f == 'i')
		len += ft_print_d_and_i(va_arg(args, int));
	else if (f == 'u')
		len += ft_print_u(va_arg(args, unsigned int));
	else if (f == 'x' || f == 'X')
		len += ft_print_xx(va_arg(args, unsigned int), f);
	else if (f == '%')
	{
		write(1, &f, 1);
		len++;
	}
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	len = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_datatype(format[i + 1], args);
			i++;
		}
		else
			len += ft_print_c(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
