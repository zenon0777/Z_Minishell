/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:30:18 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/19 01:10:14 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lst_new1(char *key, char *value)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->key = ft_strdup(key);
	if (value)
		lst->value = ft_strdup(value);
	else
		lst->value = ft_strdup("");
	lst->next = NULL;
	return (lst);
}

void	ft_lstadd_back_prime(t_env **lst, t_env *node)
{
	t_env	*head;

	head = *lst;
	if (!head)
		*lst = node;
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
	char	*key;

	h = ft_strdup(str);
	j = 0;
	a = (char) c;
	while (h[j] && h[j] != a)
		j++;
	if (h[j] + 1 == '\0')
	{
		free(h);
		return (str);
	}
	else
	{
		key = ft_substr(str, 0, j);
		free(h);
		return (key);
	}
	free(h);
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
		if (!ft_isalpha(arg[0]))
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
