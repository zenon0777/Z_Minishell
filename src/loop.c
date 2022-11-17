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

bool   set_rl(char *input, char *output, int fd, bool nl)
{
    if (input != NULL)
	{
		ft_putstr_fd(input, fd);
		ft_putstr_fd(": ", fd);
	}
	if (output != NULL)
		ft_putstr_fd(output, fd);
	ft_putendl_fd("", fd);
	if (nl)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return (true);
}

void    loop(char *input, t_list *chunks, t_as *syntax, t_env *envmap)
{
	t_fds	fd;

	while (1)
    {
		chunks = NULL;
		syntax = NULL;
		var.id = 0;
        input = readline("SHELL_BREAK > ");
		var.usr = input;
		if (!input)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
        if (!*input && set_rl(input, "", STDERR_FILENO, false))
			continue ;
        add_history(input);
        if (!quotes(input) && set_rl(input, "Quotes not paired", STDERR_FILENO, false))
            continue;
        input = expand(input, envmap, false);
        tokenizer(input, &chunks);
        syntax = ast_fill(chunks, syntax);
        if (syntax && (!check_ast(syntax) && set_rl(input, "Syntax error", STDERR_FILENO, false)))
		{
			free_ast(syntax);
			ft_lstclear(&chunks, (void *)free);
            continue ;
		}
		// ast_print(syntax);
        check_cmd(&envmap, chunks, &fd);
		free(input);
		if (syntax)
			free_ast(syntax);
		if (chunks)
			ft_lstclear(&chunks, (void *)free);
	}
}
