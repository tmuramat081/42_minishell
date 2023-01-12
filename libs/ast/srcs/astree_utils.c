#include "libast.h"

size_t  ast_count_nodes(t_ast_node *root)
{
    if (root == NULL)
        return (0);
    return (1 + ast_count_nodes(root->left) + ast_count_nodes(root->right));
}


void	append_redirect(t_command *command, t_redirect *redirect)
{
	t_redirect *tmp;

	tmp = command->redirects;
	while (tmp)
		tmp = tmp->next;
	tmp = redirect;

}

void	append_arg(t_command *command, char *word)
{
	t_arg	*tmp;

	tmp = command->args;
	while (tmp)
		tmp = tmp->next;
	tmp->arg = word;
}
