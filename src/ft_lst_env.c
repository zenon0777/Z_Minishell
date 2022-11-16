/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:54:37 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/16 21:24:31 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (lst == NULL || *lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	tmp = *lst;
	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	(*lst)->next = new;
	new->next = NULL;
	*lst = tmp;
}

t_env	*ft_lstnew_env(char *name, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->key = ft_strdup(name);
	if (value)
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	ft_free_lst_env(t_env **head)
{
	t_env		*tmp;

	while ((*head))
	{
		free((*head)->value);
		free((*head)->key);
		tmp = (*head)->next;
		free((*head));
		(*head) = tmp;
	}
}
