/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 06:26:09 by adaifi            #+#    #+#             */
/*   Updated: 2022/11/04 07:05:34 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../trees.h"

int	check_ast(t_ast *ast)
{
	if (ast->type == PIPE)
	{
		if (ast->left == NULL || ast->right == NULL)
			return (0);
	}
	if (ast->type == RD)
	{
		if (ast->left == NULL)
			return (0);
	}
	check_ast(ast->left);
	check_ast(ast->right);
	return (1);
}

void	free_ast(t_ast *ast)
{
	t_ast	*tree;

	tree = ast;
	free(ast);
	if (ast->right)
		free_ast(tree->right);
	if (ast->left)
		free_ast(tree->left);
}

t_ast	*d_add_redir_pipe(t_ast *ast, t_ast *node)
{
	if (ast->type == RD)
	{
		if (ast->right != NULL)
			ast->left = d_add_node(ast->left, node);
		else
			ast->right = d_add_node(ast->right, node);
	}
	if (ast->type == PIPE)
	{
		if (ast->right != NULL)
			ast->left = d_add_node(ast->left, node);
		else
			ast->right = d_add_node(ast->right, node);
	}
	return (ast);
}

t_ast	*d_add_node(t_ast *ast, t_ast *node)
{
	t_ast	*tree;

	if (ast == NULL)
		return (node);
	tree = ast;
	if (node->type < tree->type)
	{
		node->right = tree;
		tree = node;
	}
	else if (tree->type == node->type)
	{
		if (tree->type == PIPE)
		{
			node->right = tree;
			tree = node;
		}
		else
			tree->right = d_add_node(tree->right, node);
	}
	else
		tree = d_add_redir_pipe(tree, node);
	return (tree);
}

t_ast	*d_new_node(char *str)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (ast == NULL)
		return (NULL);
	if (!ft_strncmp(str, ">", 2) || !ft_strncmp(str, ">>", 3)
		|| !ft_strncmp(str, "<", 2) || !ft_strncmp(str, "<<", 3))
		ast->type = RD;
	else if (!ft_strncmp(str, "|", 2))
			ast->type = PIPE;
	else
		ast->type = CMD;
	ast->cmd = str;
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

t_ast	*ast_fill(t_list *lst, t_ast *syntax)
{
	t_ast	*st;

	st = NULL;
	while (lst)
	{
		syntax = d_new_node(lst->content);
		st = d_add_node(st, syntax);
		lst = lst->next;
	}
	return (st);
}
