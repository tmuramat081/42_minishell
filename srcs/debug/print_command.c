#include "terminal.h"
#include "ft_printf.h"

static void print_command(t_ast_node *node)
{
	t_argument	*curr;

	curr = node->command->arguments;
	while (curr)
	{
		ft_printf("%s\n", curr->argument);
		curr = curr->next;
	}

}

static void	print_commands_rec(t_ast_node *node)
{
	if (!node)
		return ;
	print_commands_rec(node->left);
	if (node->type & NODE_COMMAND)
		print_command(node);
	print_commands_rec(node->right);
}

void	print_commands(t_ast_node *syntax_tree)
{
	ft_printf("%s>>>> EXPANDER >>>>", CYAN);
	ft_printf("\n===============================================\n");
	print_commands_rec(syntax_tree);
	ft_printf("===============================================%s\n\n", DEFAULT);
}
