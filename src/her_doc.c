/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 17:42:09 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/17 23:39:17 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void sig_herdoc(int sig)
{
	(void)sig;
	printf("\n");
	rl_done = 0;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	her_doc(t_list *arg)
{
	char	*s;
	int	file;
	int	tmp;

	signal(SIGINT, SIG_IGN);
	file = open("/tmp/tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 00777);
	tmp = dup(file);
	s = readline(">");
	if (s == NULL || !ft_strcmp(s, arg->content))
		return (free(s), file);
	s = ft_strjoin(s, "\n");
	write(tmp, s, ft_strlen(s));
	while (ft_strcmp(s, arg->content))
	{
		free(s);
		if (signal(SIG_INT, sig_herdoc) != SIG_ERR)
		s = readline(">");
		if (s == NULL || !ft_strcmp(s, arg->content))
			return (free(s), file);
		s = ft_strjoin(s, "\n");
		write(tmp, s, ft_strlen(s));
	}
	free(s);
	return (file);
}
