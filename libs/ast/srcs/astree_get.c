#include "libast.h"

size_t  ast_count_nodes(t_ast_node *root)
{
    if (root == NULL)
        return (0);
    return (1 + ast_count_nodes(root->left) + ast_count_nodes(root->right));
}

size_t	ast_count_arguments(t_argument *arguments)
{
	size_t	count;

	count = 0;
	while (arguments)
	{
		count += 1;
		arguments = arguments->next;
	}
	return (count);
}

size_t	ast_count_redirects(t_redirect *redirects)
{
	size_t	count;

	count = 0;
	while (redirects)
	{
		count += 1;
		redirects = redirects->next;
	}
	return (count);
}

char	*ast_get_command_name(t_command *command)
{
	return (command->arguments->argument);
}