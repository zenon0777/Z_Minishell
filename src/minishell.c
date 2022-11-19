/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:40:34 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/18 23:50:19 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int sig)
{
	if (sig == 2 && var.id == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		var.exit_status = 1;
	}
	else if (sig == 2 && var.id == 1 && ft_strncmp(var.usr, "./minishell", 11))
		printf("\n");
	if (sig == 2 && var.id == 1 && !ft_strcmp(var.usr, "./minishell"))
		var.exit_status = 130;
	else if (sig == 3 && var.id == 1 && ft_strcmp(var.usr, "./minishell"))
	{
		var.exit_status = 131;
		printf("Quit: 3\n");
	}
}

// void	f()
// {
// 	system("leaks minishell");
// }

int	main(int argc, char const *argv[], char *envp[])
{
	t_env	*envmap;
	t_list	*chunks;
	t_as	*syntax;
	char	*input;

	envmap = NULL;
	chunks = NULL;
	syntax = NULL;
	input = NULL;
	(void)argv;
	(void)argc;
	// atexit(f);
	var.id = 0;
	envmap = ft_environment(envp, envmap);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	rl_catch_signals = 0;
	loop(input, chunks, syntax, envmap);
	return (0);
}
