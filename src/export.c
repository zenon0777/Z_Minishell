/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:00:32 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/14 17:24:45 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_env(t_env **env, t_list *arg)
{
	t_env	*lst;

	lst = (*env);
	ft_sort_env(env);
	// if (arg->next && ft_multiple_check(arg->next->content))
	// {
	// 	if (arg->next->ch == '"' || arg->next->ch == '\'')
	// 		return (ft_putendl_fd("Error: not a valid identifier", 2));
	// }
	if (!arg->next || ft_multiple_check(arg->next->content) == 2)
		return (ft_print_exported(env));
	while (arg)
	{
		lst = (*env);
		set_env_existed(env, arg, &lst);
		if (arg->flag == 1)
			arg = arg->next;
		if ((*env) == NULL)
		{
			(*env) = lst;
			ft_add_export(arg->next->content, env);
		}
		arg = arg->next;
	}
	return ;
}

void	set_env_existed(t_env **env, t_list *arg, t_env **lst)
{
	char	*key;
	char	*value;
	t_env	**tmp;
	char	*s;

	tmp = env;
	while ((*env) && arg->next)
	{
		s = ft_strchr(arg->next->content, '+');
		key = get_keys(arg->next->content, '=');
		if (!key || (ft_multiple_check(key) == 1 && ft_strcmp(key, "_")))
			return (var.exit_status = 1, ft_putendl_fd("Error: export", 2));
		if (!s)
			return ;
		if (s[0] == '+')
		{
			char *h = get_keys(arg->next->content, '+');
			value = ft_strchr(arg->next->content, '+') + 2;
			export_join(env, h, value);
			*env = *lst;
			return ;
		}
		(*env) =(*env)->next;
	}
	env = tmp;
	while ((*env) && arg->next)
	{
		key = get_keys(arg->next->content, '=');
		if (!ft_strcmp(key, (*env)->key))
		{
			value = (*env)->value;
			free(value);
			(*env)->value = ft_strdup(ft_strchr(arg->next->content, '=') + 1);
			*env = *lst;
			return ;
		}
		(*env) = (*env)->next;
	}
}

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
	char	*value;
	char	*key;
	t_env	*lst;

	value = ft_strchr(str, '=') + 1;
	key = get_keys(str, '=');
	if (ft_multiple_check(key) == 1)
		return (var.exit_status = 1, ft_putendl_fd("Export : error", 2));
	lst = ft_lst_new1(key, value);
	ft_lstadd_back_prime(env, lst);
}
