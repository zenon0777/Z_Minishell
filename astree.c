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
   	char    *begin;
        char    *end;

        begin = input;
        while (*begin)
        {
                while (ft_isspace(*begin))
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
