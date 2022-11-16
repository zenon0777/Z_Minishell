/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 19:38:47 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/17 00:35:06 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*redirection_handler(t_list **arg, t_fds *fds, char *str)
{
	while ((*arg) && ft_strcmp((*arg)->content, "|"))
	{
		if (!ft_strncmp((*arg)->content, "<", 1))
			input(arg, fds);
		else if (!ft_strncmp((*arg)->content, ">", 1))
			output(arg, fds);
		else
		{
			str = ft_strjoin_custom(str, (*arg)->content);
			str = ft_strjoin_custom(str, " ");
		}
		(*arg) = (*arg)->next;
	}
	return (str);
}

void	content_handler(t_list **arg, t_env **env, t_fds *fds)
{
	char	*str;
	t_list	*tmp;
	int		tmp_in;
	int		tmp_out;

	tmp = *arg;
	str = ft_strdup("");
	tmp_in = dup(0);
	tmp_out = dup(1);
	str = redirection_handler(arg, fds, str);
	if (*str == '\0')
		return (printf("command not found\n"), var.exit_status = 127, free(str));
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	execute_redir(tmp, env, fds, str);
	free(str);
}

void	execute_redir(t_list *arg, t_env **env, t_fds *fds, char *str)
{
	char	**cmd;
	int		tmp_in;
	int		tmp_out;
	int		i;

	i = 0;
	if (fds->in < 0 || fds->out < 0)
		return (var.exit_status = 1, ft_putendl_fd("fd e5rror", 2));
	cmd = ft_split(str, ' ');
	while (cmd[i])
	{
		cmd[i] = removeChar(cmd[i]);
		i++;
	}
	tmp_in = dup(0);
	tmp_out = dup(1);
	dup2(fds->in, STDIN_FILENO);
	dup2(fds->out, STDOUT_FILENO);
	close(fds->in);
	close(fds->out);
	if (check_type(cmd[0]))
		builting(env, arg);
	else if (var.i == 0)
		execute_one_cmd(cmd, env);
	else
		execute(cmd, env, fds);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	ft_free_2d(cmd);
}

void	execute(char **cmd, t_env **env, t_fds *fds)
{
	char	**envp;
	int		j;

	j = 0;
	var.id = 1;
	var.cpid = fork();
	if (var.cpid < 0)
		return (var.exit_status = 1, ft_putendl_fd("fork error", 2));
	if (var.cpid == 0)
	{
		while (j <= var.i)
		{
			close(fds->fd[j]);
			j++;
		}
		envp = env_str(*env);
		if (execve(get_path(cmd[0], env), cmd, envp) == -1
			|| check_upper(cmd[0]) || !get_path(cmd[0], env))
		{
			ft_free_2d(envp);
			ft_free_2d(cmd);
			return (ft_putendl_fd("command not found", 2), exit(127));
		}
		ft_free_2d(envp);
	}
}

void	execute_one_cmd(char **cmd, t_env **env)
{
	char	**envp;
	int		stat;

	var.id = 1;
	stat = 0;
	var.cpid = fork();
	if (var.cpid == 0)
	{
		envp = env_str(*env);
		if (execve(get_path(cmd[0], env), cmd, envp) == -1
			|| check_upper(cmd[0]) || !get_path(cmd[0], env))
		{
			ft_free_2d(envp);
			ft_free_2d(cmd);
			return (ft_putendl_fd("command not found", 2), exit(127));
		}
		ft_free_2d(envp);
	}
	wait(&stat);
	var.exit_status = WEXITSTATUS(stat);
}

void	execute_pipe(t_env *env, t_list *arg, t_fds *fds, int i)
{
	int		j;
	int		tmp_in;
	int		tmp_out;

	j = 0;
	fds->fd = (int *)malloc((i * 2) * sizeof(int));
	tmp_in = dup(0);
	tmp_out = dup(1);
	while (j < i * 2)
	{
		pipe(fds->fd + j);
		j += 2;
	}
	i = i + 1;
	pipe_handler(fds, arg, env, i);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	close(tmp_in);
	close(tmp_out);
	close(fds->in);
	close(fds->out);
	free(fds->fd);
}
