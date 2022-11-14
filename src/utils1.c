/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:17:24 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/14 17:20:41 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	**env_str(t_env *env)
{
	char	*str;
	char	**envp;

	str = ft_strdup("");
	while (env)
	{
		str = ft_strjoin(str, env->key);
		str = ft_strjoin(str, "=");
		str = ft_strjoin(str, env->value);
		str = ft_strjoin(str, "$");
		env = env->next;
	}
	envp = ft_split(str, '$');
	free(str);
	return (envp);
}

void	input(t_list **arg, t_fds *fds)
{
	int		tmp;

	if (!ft_strcmp((*arg)->content, "<<"))
	{
		(*arg) = (*arg)->next;
		 // => https://stackoverflow.com/questions/70672456/how-here-document-works-in-shell
		close(her_doc(*arg));
		tmp = open("/tmp/tmpfile", O_RDONLY, 00777);
		unlink("/tmp/tmpfile");
		dup2(tmp, fds->in);
		close(tmp);
	}
	else
	{
		close(fds->in);
		(*arg) = (*arg)->next;
		fds->in = open((*arg)->content, O_RDWR, 0777);
	}
}

void	output(t_list **arg, t_fds *fds)
{
	close(fds->out);
	if (!ft_strcmp((*arg)->content, ">>"))
	{
		(*arg) = (*arg)->next;
		fds->out = open((*arg)->content, O_APPEND | O_CREAT | O_WRONLY, 00777);
	}
	else
	{
		(*arg) = (*arg)->next;
		fds->out = open((*arg)->content, O_CREAT | O_WRONLY | O_TRUNC, 00777);
	}
}

void	pipe_handler(t_fds *fds, t_list *arg, t_env *env, int i)
{
	int		j;
	int		stat;

	stat = 0;
	j = -1;
	while (arg && ++j < i)
	{
		if (j == 0)
		{
			fds->in = dup(0);
			fds->out = dup(fds->fd[(j * 2) + 1]);
		}
		else if (j < i && j != i - 1)
		{
			fds->out = dup(fds->fd[(j * 2) + 1]);
			fds->in = dup(fds->fd[(j - 1) * 2]);
		}
		else if (j == i - 1)
		{
			fds->in = dup(fds->fd[(j - 1) * 2]);
			fds->out = dup(1);
		}
		content_handler(&arg, &env, fds);
		if (arg && arg->next != NULL)
			arg = arg->next;
		close(fds->fd[(j * 2) + 1]);
	}
	j = 0;
	while (j < i)
	{
		close(fds->fd[j]);
		j++;
	}
	j = 0;
	while(j <= i)
	{
		wait(NULL);
		j++;
	}
	var.exit_status = WEXITSTATUS(stat);
}
