/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:43:28 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/18 22:35:12 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_dfl(int sig)
{
	(void)sig;
	printf("\n");
	exit(130);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	execute_pipe(t_env *env, t_list *arg, t_fds *fds, int i)
{
	int		j;
	int		tmp_in;
	int		tmp_out;

	j = 0;
	fds->fd = (int *)malloc((i * 2) * sizeof(int));
	if (fds->fd == NULL)
		return ;
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
