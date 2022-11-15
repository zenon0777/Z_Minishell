/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:30:18 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/15 09:49:53 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

t_env	*ft_lst_new1(char *key, char *value)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = ft_strdup(key);
	lst->value = ft_strdup(value);
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back_prime(t_env **lst, t_env *node)
{
	t_env	*head;

	head = *lst;
	if (!head)
	{
		*lst = node;
	}
	else
	{
		while (head && head->next)
			head = head->next;
		head->next = node;
	}
}

char	*get_keys(char *str, int c)
{
	char	*h;
	char	a;
	int		j;

	h = str;
	j = 0;
	a = (char) c;
	while (h[j] && h[j] != a)
		j++;
	if (h[j] + 1 == 0)
		return (str);
	else
	{
		h[j] = 0;
		return (h);
	}
	return (str);
}

int	ft_multiple_check(char *arg)
{
	int		i;

	i = 1;
	while (arg[i])
	{
		if ((arg[0] == '>' || arg[0] == '|' || arg[0] == '<'))
			return (2);
		if (!ft_isalpha(arg[0]) || arg[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_upper(char *str)
{
	if (str[0] >= 'A' && str[0] <= 'Z')
		return (1);
	return (0);
}
