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

#define PIPE 0
#define CMD 2
#define RD 1

typedef struct astrees
{
//    enum type{ RD, CMD, PIPE, QA };
   char    *cmd;
   struct astrees *left;
   struct astrees *right;
   int		type;
}   t_ast;

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
    struct syntax  *next;
}   t_syntax;

void	tokenizer(char *input, t_list **chunks);
int     check_input_char(char c);
t_env	*ft_environment(char **envp, t_env *env);
void	ft_while_env(t_env **env, char **envp, t_env **node, int *i);
void	env_env(t_env *env);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstnew_env(char *name, char *value);
void	ft_free_lst_env(t_env **head);
t_ast   *ast_fill(t_list *lst, t_ast *syntax);
t_ast *d_add_node(t_ast *ast, t_ast *node);
t_ast *d_new_node(char *str);

#endif
