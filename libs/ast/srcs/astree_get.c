#include "libast.h"

size_t  ast_count_nodes(t_ast_node *root)
{
    if (root == NULL)
        return (0);
    return (1 + ast_count_nodes(root->left) + ast_count_nodes(root->right));
}

char	*ast_get_command_name(t_command *command)
{
	return (command->arguments->argument);
}