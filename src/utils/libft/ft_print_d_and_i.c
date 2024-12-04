/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_and_i.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:59:50 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/04 13:37:25 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_d_and_i(int num)
{
	int		len;
	char	*mem_to_free;

	len = 0;
	mem_to_free = ft_itoa(num);
	len = ft_print_s(mem_to_free);
	gb_free(mem_to_free);
	return (len);
}
