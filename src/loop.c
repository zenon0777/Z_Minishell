/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:33:53 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/19 02:12:02 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ast_print(t_as *ast)
{
	printf("root : %s\n", ast->cmd);
	if (ast->left)
	{
		printf("left of : %s\n", ast->cmd);
		ast_print(ast->left);
	}
	if (ast->right)
	{
		printf("right of : %s\n\n", ast->cmd);
		ast_print(ast->right);
	}
}

int	quotes(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '\"')
			cmd = ft_strchr(cmd + 1, '\"');
		if (cmd == NULL)
			return (0);
		if (*cmd == '\'')
			cmd = ft_strchr(cmd + 1, '\'');
		if (cmd == NULL)
			return (0);
		++cmd;
	}
	return (1);
}

bool	set_rl(char *input, char *output, int fd)
{
	if (input != NULL)
	{
		ft_putstr_fd(input, fd);
		ft_putstr_fd(": ", fd);
	}
	if (input != NULL && output)
	{
		ft_putstr_fd(output, fd);
		ft_putstr_fd("\n", 0);
	}
	return (true);
}

void	loop(char *input, t_list *chunks, t_as *syntax, t_env *envmap)
{
	t_fds	fd;

	while (1)
	{
		chunks = NULL;
		syntax = NULL;
		var.id = 0;
		input = readline("SHELL_BREAK > ");
		var.usr = ft_strtrim(input, "\t ");
		if (!input)
		{
			free(input);
			free(var.usr);
			write(1, "exit\n", 5);
			exit(0);
		}
		if (!*input && set_rl(NULL, "", 2))
		{
			free(input);
			free(var.usr);
			continue ;
		}
		add_history(input);
		if (!quotes(input) && set_rl(input, "Quotes error", 2))
			continue ;
		input = expand(input, envmap, false);
		tokenizer(input, &chunks);
		syntax = ast_fill(chunks, syntax);
		// ast_print(syntax);
		if ((!check_ast(syntax) && set_rl(input, "Syntax error", 2)))
		{
			free_ast(syntax);
			ft_lstclear(&chunks, (void *)free);
			continue ;
		}
		check_cmd(&envmap, chunks, &fd);
		free(input);
		free(var.usr);
		if (syntax)
			free_ast(syntax);
		if (chunks)
			ft_lstclear(&chunks, free);
	}
}
