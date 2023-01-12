#include "libast.h"
#include <stdlib.h>

t_command  *ast_command_create(void)
{
	t_command *command;

	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->redirects = NULL;
	return (command);
}

t_ast_node  *ast_node_create(void)
{
	t_ast_node *node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->command = ast_command_create();
	if (!node->command)
	{
		ast_node_delete(node);
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
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