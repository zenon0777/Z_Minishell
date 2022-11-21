/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:23:53 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/21 01:59:12 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_join(t_env **env, t_list *arg, char *key, char *value)
{
	t_env	*lst;

	lst = *env;
	while (*env)
	{
		if (!ft_strcmp(key, (*env)->key) && value)
		{
			(*env)->value = ft_strjoin_custom((*env)->value, value);
			break ;
		}
		*env = (*env)->next;
	}
	if (*env == NULL)
	{
		*env = lst;
		ft_add_export(arg->next->content, env);
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

void	ft_add_export(char *str, t_env **env)
{
	t_env	*lst;
	char	*value;
	char	*key;

	value = ft_strchr(str, '=');
	key = get_keys(str, '=');
	if (value)
		value = value + 1;
	if (ft_multiple_check(key) == 1)
		return (var.exit_status = 1, ft_putendl_fd("Export : error", 2));
	lst = ft_lst_new1(key, value);
	free(key);
	ft_lstadd_back_prime(env, lst);
}
