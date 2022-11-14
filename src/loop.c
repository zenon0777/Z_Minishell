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
	t_list	*tmp = NULL;

    while (1)
    {
		tmp = NULL;
        input = readline("SHELL_BREAK > ");
        // if (!input && set_rl(input, "", STDERR_FILENO, false))
		// 	continue ;
        add_history(input);
        if (!quotes(input) && set_rl(input, "Quotes not paired", STDERR_FILENO, false))
            continue;
        input = expand(input, envmap, false);
        tokenizer(input, &chunks);
        syntax = ast_fill(chunks, syntax);
		ast_print(syntax);
        if (!check_ast(syntax) && set_rl(input, "Syntax error", STDERR_FILENO, false))
            continue ;
        ft_free((void **)&input);
        check_cmd(&envmap, chunks, &fd);
    }
}