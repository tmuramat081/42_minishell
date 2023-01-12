#include "libast.h"

size_t  ast_count_nodes(t_ast_node *root)
{
    if (root == NULL)
        return (0);
    return (1 + ast_count_nodes(root->left) + ast_count_nodes(root->right));
}


t_command  *command_create(void)
{
	t_command *command;

	command = ft_xmalloc(sizeof(t_command));
	command->arg = ft_deque_init(sizeof(char *), 1);
	command->redirect = ft_deque_init(sizeof(char *), 1);
	return (command);
}

void	append_word(t_deque *list, void *word)
{
	if (!ft_deque_push_back(list, &word))
		exit(EXIT_FAILURE);
}
