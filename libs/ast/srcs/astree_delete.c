#include "libast.h"
#include <stdlib.h>

void 	ast_arguments_delete(t_argument *argument)
{
	t_argument	*tmp;

	while (argument)
	{
		tmp = argument->next;
		free(tmp->argument);
		argument = tmp;
	}
	free(argument);
}

void	ast_redirects_delete(t_redirect *redirect)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		tmp = redirect->next;
		free(tmp->file);
		free(tmp);
		tmp = tmp->next;
	}
	free(redirect);
}

void	ast_command_delete(t_command *command)
{
	if (!command)
		return ;
	ast_redirects_delete(command->redirects);
	ast_arguments_delete(command->arguments);
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