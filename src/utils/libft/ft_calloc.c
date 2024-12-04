/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:48:11 by jodiaz-a          #+#    #+#             */
/*   Updated: 2023/11/10 13:49:42 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmeb, size_t size)
{
	void			*p;
	unsigned int	taille;

	p = NULL;
	if (size == 0 || nmeb == 0)
		return (malloc(0));
	taille = nmeb * size;
	if (nmeb && size && ((taille / nmeb) == size))
		p = malloc(taille);
	if (!p)
		return (NULL);
	ft_bzero(p, taille);
	return (p);
}
