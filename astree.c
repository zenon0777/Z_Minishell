/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:51:38 by adaifi            #+#    #+#             */
/*   Updated: 2022/10/27 19:14:28 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trees.h"


int check_input_char(char c)
{
    if (c == '\'' || c == "\"")
        return QA;
    if (c == '<' || c == '>')
        return RD;
    if (c == '|')
        return PIPE;
    else
        return 0;
}

t_token *ft_string_handl(t_token **tok, char *str, int *i)
{

}

t_token *ft_pipe_handl(t_token **tok, char *str, int *i)
{

}

t_token *ft_rd_handl(t_token **tok, char *str, int *i)
{

}

t_token *tokenizer(char *input, t_token **tok)
{
    int i = 0;
    while(input[i])
    {
        if (check_input_char(input[i]) == QA || check_input_char(input[i]) == 0)
            ft_string_handl(&tok, input, &i);
        else if (check_input_char(input[i]) == RD)
            ft_rd_handl(&tok, input, &i);
        else if (check_input_char(input[i]) == PIPE)
            ft_pipe_handl(&tok, input, &i);
        i++;
    }   
}

int main(int argc, char const *argv[])
{
    char    *rl;
    t_token *tok;

    while (1)
    {
        rl = readline("mini>");
        if (!rl)
            return (free(rl));
        add_history(rl);
        tokenizer(rl, &tok);
    }
    return 0;
}
