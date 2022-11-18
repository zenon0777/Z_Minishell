/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:23:53 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/18 15:26:05 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_join(t_env **env, char *key, char *value)
{
	while (*env)
	{
		if (!ft_strcmp(key, (*env)->key))
		{
			(*env)->value = ft_strjoin((*env)->value, value);
			break ;
		}
		*env = (*env)->next;
	}
}

void	ft_sort_env(t_env **env)
{
	t_env	*top;
	t_env	*tmp;
	int		i;

	tmp = *env;
	top = *env;
	while (top)
	{
		i = 0;
		*env = tmp;
		while (*env)
		{
			if (ft_strcmp(top->key, (*env)->key) > 0)
				i++;
			*env = (*env)->next;
		}
		top->index = i;
		top = top->next;
	}
	*env = tmp;
	top = tmp;
}

void	ft_add_export(char *key, char *value, t_env **env)
{
	t_env	*lst;

	if (value)
		value = value + 1;
	if (ft_multiple_check(key) == 1)
		return (var.exit_status = 1, ft_putendl_fd("Export : error", 2));
	lst = ft_lst_new1(key, value);
	ft_lstadd_back_prime(env, lst);
}
