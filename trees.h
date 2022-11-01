/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:52:06 by adaifi            #+#    #+#             */
/*   Updated: 2022/10/31 18:54:10 by adaifi           ###   ########.fr       */
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

typedef struct environment
{
	char				*key;
	char				*value;
	int					index;
	int					yes;
	struct environment	*next;
}t_env;

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
int     check_input_char(char c);
t_env	*ft_environment(char **envp, t_env *env);
void	ft_while_env(t_env **env, char **envp, t_env **node, int *i);
void	env_env(t_env *env);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
void	ft_free_lst_env(t_env **head);

#endif
