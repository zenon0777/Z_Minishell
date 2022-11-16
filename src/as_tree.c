#include "../minishell.h"

int	check_ast(t_as *ast)
{
	t_as	*pre;

	pre = ast->right;
	if (ast->type == PIPE)
	{
		if ((ast->left == NULL || ast->right == NULL))
			return (0);
		if (ast->right->type == PIPE && pre->right == NULL)
			return 0;
	}
	if (ast->type == RD)
	{
		if (ast->left == NULL || (pre && pre->type == RD))
			return (0);
	}
	if (ast->left != NULL && ast->right != NULL)
		if (!check_ast(ast->left) || !check_ast(ast->right))
			return 0;
	return (1);
}

void	free_ast(t_as *ast)
{
	t_as	*tree;

	tree = ast;
	if (tree->right)
		free_ast(tree->right);
	if (tree->left)
		free_ast(tree->left);
	free(ast);
}

t_as	*d_add_redir_pipe(t_as *ast, t_as *node)
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

t_as	*d_add_node(t_as *ast, t_as *node)
{
	t_as	*tree;

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

t_as	*d_new_node(char *str)
{
	t_as	*ast;

	ast = (t_as *)malloc(sizeof(t_as));
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

t_as	*ast_fill(t_list *lst, t_as *syntax)
{
	t_as	*st;

	st = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst)
	{
		syntax = d_new_node(lst->content);
		st = d_add_node(st, syntax);
		lst = lst->next;
	}
	return (st);
}