#include "libast.h"
#include <stdlib.h>

t_ast_node  *ast_node_create(void)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node))
	if (!node)
		return;
	root->left = NULL;
	root->right = NULL;
	return (node);
}

t_ast_node *ast_parent_create(t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node;

	node = ast_node_create();
	if (!node)
		return (NULL);
	node->left = left;
	node->right = right;
	return (node);
}