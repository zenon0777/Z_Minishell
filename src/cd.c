/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:55:52 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/16 20:40:01 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	cd_home(t_env *env)
{
	t_env	*lst;
	char	*home;
	char	oldpwd[1024];

	lst = env;
	home = NULL;
	getcwd(oldpwd, 1024);
	while (env)
	{
		if (!ft_strcmp(env->key, "HOME"))
		{
			home = env->value;
			break ;
		}
		env = env->next;
	}
	if (!home && !env)
		return (var.exit_status = 1, ft_putendl_fd("Home not set", 2));
	else
		chdir(home);
	update_pwd(&lst, oldpwd);
}

void	cd(t_env *env, t_list *arg)
{
	t_env	*lst;
	char	oldpwd[1024];

	lst = env;
	getcwd(oldpwd, 1024);
	if (!arg->next || ft_multiple_check(arg->next->content) == 2)
		cd_home(env);
	while (arg->next)
	{
		if (ft_multiple_check(arg->next->content) == 2)
			break ;
		if (chdir(arg->next->content))
		{
			var.exit_status = 1;
			return (ft_putendl_fd("No such file or directory", 2));
		}
		update_pwd(&lst, oldpwd);
		arg = arg->next;
	}
}

void	update_pwd(t_env **lst, char *home)
{
	t_env	*env;
	char	pwd[1024];
	t_env	*node;

	env = (*lst);
	node = *lst;
	while ((*lst))
	{
		if (!ft_strcmp((*lst)->key, "PWD"))
		{
			free((*lst)->value);
			getcwd(pwd, 1024);
			(*lst)->value = ft_strdup(pwd);
		}
		else if (!ft_strcmp((*lst)->key, "OLDPWD"))
		{
			free((*lst)->value);
			(*lst)->value = ft_strdup(home);
			break ;
		}
		(*lst) = (*lst)->next;
	}
	if (!(*lst))
	{
		node = ft_lst_new1("PWD", getcwd(pwd, 1024));
		ft_lstadd_back_prime(&env, node);
		node = ft_lst_new1("OLDPWD", home);
		ft_lstadd_back_prime(&env, node);
	}
}
