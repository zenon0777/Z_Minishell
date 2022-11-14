#include "../minishell.h"

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
    while (1)
    {
        ft_free((void **)&input);
        input = readline("SHELL_BREACK > ");
        if (!input)
        {
            ft_putendl_fd("exit", STDOUT_FILENO);
            exit(0);
        }
        add_history(input);
        /* need check value of quotes */
        if (!quotes(input) && set_rl(input, "Quotes not paired", STDERR_FILENO, false))
            continue;
        input = expand(input, envmap, false);
        /* need check value of input */
        tokenizer(input, &chunks);
        /* need check value of chunks */
        syntax = ast_fill(chunks, syntax);
        if (!check_ast(syntax) && set_rl(input, "Syntax error", STDERR_FILENO, false))
            continue ;
        // check_cmd(&envmap, chunks, &fd);
    }
}