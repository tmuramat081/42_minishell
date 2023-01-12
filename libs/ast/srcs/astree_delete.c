#include "libast.h"
#include <stdlib.h>


void	ast_command_delete(t_ast_node *command)
{
	free(command);
}

void ast_node_delete(t_ast_node *node)
{
    if (!node)
        return;
    if (node->command)
        free(node->command);
	ast_node_delete(node->left);
	ast_node_delete(node->right);
	free(node);
}