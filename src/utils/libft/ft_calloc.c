/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tclaereb <tclaereb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:48:11 by jodiaz-a          #+#    #+#             */
/*   Updated: 2024/12/04 13:35:40 by tclaereb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void			*p;
	unsigned int	taille;

	p = NULL;
	if (size == 0 || nmeb == 0)
		return (gb_malloc(0));
	taille = nmeb * size;
	if (nmeb && size && ((taille / nmeb) == size))
		p = gb_malloc(taille);
	if (!p)
		return (NULL);
	ft_bzero(p, taille);
	return (p);
}
