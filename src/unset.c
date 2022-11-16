/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 17:01:26 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/16 21:31:57 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_env	*unset(t_env *env, t_env *tmp, t_list *arg)
{
	t_env	*lst;

	while (env)
	{
		if (ft_strcmp(env->key, arg->content))
		{
			lst = ft_lst_new1(env->key, env->value);
			ft_lstadd_back_prime(&tmp, lst);
		}
		env = env->next;
	}
	return (tmp);
}

void	unset_env(t_env **env, t_list *arg)
{
	t_env	*tmp;
	t_env	*env_back;
	char	*str;

	tmp = NULL;
	str = NULL;
	while (arg && env)
	{
		str = arg->content;
		env_back = (*env);
		if (str[0] == '>' || str[0] == '|' || str[0] == '<')
			return ;
		if (ft_multiple_check(str) == 1 && ft_strcmp(&str[0], "_"))
		{
			var.exit_status = 2;
			ft_putendl_fd("invalide inditifier", 2);
		}
		tmp = unset(*env, tmp, arg);
		(*env) = env_back;
		free_env(*env);
		arg = arg->next;
		*env = tmp;
		tmp = NULL;
	}
}

void	free_env(t_env *env)
{
	t_env	*env_back;

	while (env)
	{
		env_back = env;
		free(env->key);
		free(env->value);
		free(env);
		env = env_back->next;
	}
	free(env);
}
