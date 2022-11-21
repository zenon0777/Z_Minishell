/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:18:38 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/20 19:18:45 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*elements;

	if (!lst || !f)
		return (NULL);
	elements = ft_lstnew(f(lst->content));
	if (elements == NULL)
		return (NULL);
	newlist = elements;
	lst = lst->next;
	while (lst)
	{
		elements = ft_lstnew(f(lst->content));
		if (!elements)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, elements);
		lst = lst->next;
	}
	return (newlist);
}
