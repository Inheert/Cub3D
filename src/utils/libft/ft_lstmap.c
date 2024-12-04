/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodiaz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:36:40 by jodiaz-a          #+#    #+#             */
/*   Updated: 2023/11/08 11:47:20 by jodiaz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*start;
	void	*re;

	if (!lst || !f || !del)
		return (NULL);
	start = NULL;
	while (lst)
	{
		re = (*f)(lst->content);
		new = ft_lstnew(re);
		if (!new)
		{
			del(re);
			ft_lstclear(&start, del);
			return (start);
		}
		ft_lstadd_back(&start, new);
		lst = lst->next;
	}
	return (start);
}
