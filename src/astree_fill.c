#include"../trees.h"

t_ast	*d_add_redir(t_ast *ast, t_ast *node)
{
	if (node->type == RD)
	{
		if (ast->right == NULL)
			ast->right = d_add_node(ast->right, node);
		else
			ast->left = d_add_node(ast->left, node);
	}
	if (node->type == PIPE)
	{
		if (ast->right != NULL)
			ast->left = d_add_node(ast->left, node);
		else
			ast->right = d_add_node(ast->right, node);
	}
	return ast;
}

t_ast	*d_add_node(t_ast *ast, t_ast *node)
{
	t_ast *tree;
	
	if (ast == NULL)
		return (node);
	tree = ast;
	if (node->type > tree->type)
		tree->right = node;
	else if (tree->type == node->type)
	{
		if (tree->type == PIPE)
		{
			ast->right = node;
			tree = ast;
		}
		else
			tree->right = d_add_node(tree->right, node);
	}
	else if (tree->type > node->type)
		tree = d_add_redir(tree, node);
	return (tree);
}

t_ast	*d_new_node(char *str)
{
	t_ast *ast;
	ast = (t_ast *)malloc(sizeof(t_ast));
	
	if (ast == NULL)
		return NULL;
	if (!ft_strncmp(str, ">", 2) || !ft_strncmp(str, ">>", 3) || !ft_strncmp(str, "<", 2)
			|| !ft_strncmp(str, "<<", 3))
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
	t_ast *st;

	st =NULL;
	while(lst)
	{
		syntax = d_new_node(lst->content);
		st = d_add_node(st, syntax);
		lst = lst->next;
	}
	return (st);
}
