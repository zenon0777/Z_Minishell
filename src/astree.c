/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:51:38 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/03 19:27:16 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../trees.h"
#include <unistd.h>
#include <stdlib.h>

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

/*int check_input_char(char c)
{
    if (c == '\'' || c == '"')
        return QA;
    if (c == '<' || c == '>')
        return RD;
    if (c == '|')
        return PIPE;
    else
        return */

char    *tokenize_internal(char *input, char *begin, char *end, t_list **chunks)
{
        char    *token;
        t_list   *temp;

        token = ft_substr(input, begin - input, end - begin + 1);
        temp = ft_lstnew(token);
        ft_lstadd_back(chunks, temp);
        return (end + 1);
}

void    tokenizer(char *input, t_list **chunks)
{
        char    *begin;
        char    *end;

        begin = input;
        while (*begin)
        {
                while (*begin == ' ')
                        ++begin;
                end = begin;
                while (*end && !ft_strchr(" ><|", *begin))
                {
                        if (ft_strchr("\'\"", *end))
                                end = ft_strchr(end + 1, *end);
                        if (ft_strchr("><|", *(end + 1))
                                || (*end != '\\' && *(end + 1) == ' '))
                                break ;
                        ++end;
                }
                if (!*end)
                        --end;
                if (*begin && *begin == *(begin + 1) && ft_strchr("><", *begin))
                        ++end;
                if (*begin)
                        begin = tokenize_internal(input, begin, end, chunks);
        }
}

void ast_print(t_ast *ast)
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

int main(int    ac, char **av, char **envp)
{
    char    *rl;
    t_ast	*ast;
    t_list	*syntax;
    t_env       *env;
    syntax = NULL;
    (void)ac;
    (void)envp;
    (void)av;

    env = NULL;
    ast = NULL;
   // env = ft_environment(envp, env);
    while (1)
    {
        rl = readline("mini>");
        if (!rl)
            return (free(rl), 1);
        add_history(rl);
	if (!quotes(rl))
        {
		puts("quotes error");
                free(rl);
                rl_on_new_line();
                rl_redisplay();
		continue ;
        }
        //ft_expand(rl, env);
      	tokenizer(rl, &syntax);
	ast = ast_fill(syntax, ast);
        ast_print(ast);
    }
    return 0;
}
