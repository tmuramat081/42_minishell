#include "libast.h"
#include <stdlib.h>

void 	ast_argument_delete(t_argument *argument)
{
	t_argument	*tmp;
	while (tmp)
	{
		tmp = argument->next;
		free(tmp->argument);
		tmp = tmp->next;
	}
	free(argument);
}

void	ast_redirect_delete(t_redirect *redirect)
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
	ast_redirect_delete(command->redirects);
	ast_argument_delete(command->arguments);
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