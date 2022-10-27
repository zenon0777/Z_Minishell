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

typedef struct astrees
{
    enum type{ RD, CMD, PIPE, QA };
    union
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

typedef struct  lst
{
    t_astrees   *syntax;
    struct lst  *next;
}   t_lst;

#endif