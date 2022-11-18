/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:32:48 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/18 14:39:45 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	check_type(char *arg)
{
	if (arg == NULL)
		return (0);
	if (!ft_strcmp(arg, "pwd") || !ft_strcmp(arg, "PWD"))
		return (1);
	else if (!ft_strcmp(arg, "export") || !ft_strcmp(arg, "EXPORT"))
		return (1);
	else if (!ft_strcmp(arg, "unset") || !ft_strcmp(arg, "UNSET"))
		return (1);
	else if (!ft_strcmp(arg, "env") || !ft_strcmp(arg, "ENV"))
		return (1);
	else if (!ft_strcmp(arg, "exit") || !ft_strcmp(arg, "EXIT"))
		return (1);
	else if (!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "CD"))
		return (1);
	else if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "ECHO"))
		return (1);
	return (0);
}

void	builting(t_env **env, t_list *arg)
{
	if (!ft_strcmp(arg->content, "pwd") || !ft_strcmp(arg->content, "PWD"))
		pwd_env();
	else if (!ft_strcmp(arg->content, "cd") || !ft_strcmp(arg->content, "CD"))
		cd(*env, arg);
	else if (!ft_strcmp(arg->content, "unset") || !ft_strcmp(arg->content, "UNSET"))
		unset_env(env, arg);
	else if (!ft_strcmp(arg->content, "echo") || !ft_strcmp(arg->content, "ECHO"))
		echo(arg);
	else if (!ft_strcmp(arg->content, "export") || !ft_strcmp(arg->content, "EXPORT"))
		export_env(env, arg);
	else if (!ft_strcmp(arg->content, "env") || !ft_strcmp(arg->content, "ENV"))
		env_env(*env);
	else if (!ft_strcmp(arg->content, "exit") || !ft_strcmp(arg->content, "EXIT"))
		d_exit(arg);
}

void	d_exit(t_list *arg)
{
	char	*s;

	if (!arg->next)
		exit(var.exit_status);
	s = arg->next->content;
	if (arg->next && ft_isalpha(s[0]))
		return (ft_putendl_fd("invalide args", 2), exit(255));
	else if (arg->next->next)
		return (var.exit_status = 1, ft_putendl_fd("too many args", 2));
	else if (arg->next)
		exit(ft_atoi(arg->next->content));
}

void	check_cmd(t_env **env, t_list *arg, t_fds *fds)
{
	t_list	*tmp;
	int		stat;

	stat = 0;
	var.i = 0;
	if (!arg)
		return ;
	tmp = arg;
	while (tmp)
	{
		if (!ft_strcmp(tmp->content, "|"))
			var.i++;
		tmp = tmp->next;
	}
	if (var.i == 0)
	{
		fds->in = dup(STDIN_FILENO);
		fds->out = dup(STDOUT_FILENO);
		content_handler(&arg, env, fds);
	}
	else
		execute_pipe(*env, arg, fds, var.i);
}
