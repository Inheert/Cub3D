/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_and_i.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:59:50 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/02/18 18:31:31 by jodiaz-a         ###   ########.fr       */
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
	free(mem_to_free);
	return (len);
}