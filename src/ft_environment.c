/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 07:00:13 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/16 21:29:20 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_env	*ft_environment(char **envp, t_env *env)
{
	t_env	*node;
	int		i;
	char	pwd[1024];

	i = 0;
	node = env;
	if (envp[0] == NULL)
	{
		getcwd(pwd, 1024);
		node = ft_lstnew_env("PWD", pwd);
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("OLDPWD", "");
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("SHLVL", "1");
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("_", "/usr/bin/env");
		ft_lstadd_back_env(&env, node);
		node = ft_lstnew_env("PATH", "/Users/adaifi/Desktop/parse");
		ft_lstadd_back_env(&env, node);
		return (env);
	}
	while (envp[i])
		ft_while_env(&env, envp, &node, &i);
	return (env);
}

void	ft_while_env(t_env **env, char **envp, t_env **node, int *i)
{
	char	**ptr;

	ptr = ft_split(envp[*i], '=');
	*node = ft_lstnew_env(ptr[0], ptr[1]);
	ft_lstadd_back_env(env, *node);
	(*i)++;
	ft_free_2d(ptr);
}
