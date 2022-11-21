/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:00:32 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/21 01:58:28 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_env(t_env **env, t_list *arg)
{
	t_env	*lst;
	char	*tmp;

	lst = (*env);
	ft_sort_env(env);
	if (arg->next && ft_multiple_check(arg->next->content))
		return (ft_putendl_fd("Error: not a valid identifier", 2));
	if (ft_strcmp(arg->content, "export") && arg->next->next)
		arg = arg->next->next;
	if (!arg->next || ft_multiple_check(arg->next->content) == 2)
		return (ft_print_exported(env));
	while (arg && arg->next)
	{
		lst = *env;
		tmp = arg->next->content;
		arg->next->content = removechar(tmp);
		free(tmp);
		if (set_env_existed(env, arg, &lst) && (*env) == NULL)
		{
			*env = lst;
			ft_add_export(arg->next->content, env);
		}
		arg = arg->next;
	}
	return ;
}

int	set_env_existed(t_env **env, t_list *arg, t_env **lst)
{
	t_env	*tmp;

	tmp = *env;
	if (ft_append(env, arg, lst))
	{
		*env = tmp;
		if (ft_replace(env, arg, lst) == 0)
			return (0);
	}
	return (1);
}

int	ft_append(t_env **env, t_list *arg, t_env **lst)
{
	char	*key;
	char	*value;
	char	*s;

	while (*env && arg && arg->next)
	{
		s = ft_strchr(arg->next->content, '+');
		key = get_keys(arg->next->content, '+');
		if (!key || (ft_multiple_check(key) == 1 && ft_strcmp(key, "_")))
			return (var.exit_status = 1, free(key), ft_putendl_fd("Error", 2), 1);
		if (!s)
			return (free(key), 1);
		if (s[0] == '+')
		{
			value = s + 2;
			export_join(env, arg, key, value);
			*env = *lst;
			return (free(key), 0);
		}
		free(key);
		*env = (*env)->next;
	}
	return (0);
}

int	ft_replace(t_env **env, t_list *arg, t_env **lst)
{
	char	*key;
	char	*value;

	while (*env && arg && arg->next)
	{
		key = get_keys(arg->next->content, '=');
		value = ft_strchr(arg->next->content, '=');
		if (value)
			value = value + 1;
		if (!ft_strcmp(key, (*env)->key) && value)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(value);
			*env = *lst;
			free(key);
			return (0);
		}
		free(key);
		*env = (*env)->next;
	}
	return (1);
}

void	ft_print_exported(t_env **env)
{
	t_env	*tmp;
	t_env	*top;
	int		i;

	tmp = *env;
	top = *env;
	i = 0;
	while (tmp)
	{
		(*env) = top;
		while ((*env))
		{
			if ((*env)->key && (*env)->value && (*env)->index == i)
			{
				printf("declare -x %s=\"%s\"\n", (*env)->key, (*env)->value);
				i++;
				break ;
			}
			(*env) = (*env)->next;
		}
		tmp = tmp->next;
	}
	(*env) = top;
}
