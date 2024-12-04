/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isgraph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <jodiaz-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:54:19 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/08/31 13:18:21 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * checks for any printable character 
 * not space, tabs, etc. from ascii 33 to 126
 * if the character is printable == 1
 * otherwise == 0
 */
int	ft_isgraph(int arg)
{
	if (arg > 32 && arg < 127)
		return (1);
	return (0);
}