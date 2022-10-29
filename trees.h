/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:52:06 by adaifi            #+#    #+#             */
/*   Updated: 2022/10/27 18:02:01 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREES_H
#define TREES_H
#include"libft/libft.h"
#include <stdlib.h>
#include <string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include <unistd.h>


typedef struct astrees
{
    //enum type{ RD, CMD, PIPE, QA };
    union tree
    {
        char    *tokens;
        struct
        {
            struct astrees *left;
            struct astrees *right;
        }ast_node;
        
    } tree;

}   t_astrees;

typedef struct token_s
{
    char    *input;
    char    *text;
}   t_token;

typedef struct  syntax
{
    char   *syntax;
    struct lst  *next;
}   t_syntax;

void	tokenizer(char *input, t_list **chunks);
int check_input_char(char c);

#endif
