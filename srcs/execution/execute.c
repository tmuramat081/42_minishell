#include "libast.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

char	**init_arguments(t_ast_node *node, t_shell *msh)
{
	char	**args;
	size_t	i;

	(void)msh;
	args = (char **)malloc(sizeof(t_ast_node *) * 10);
	i = 0;
	while (node)
	{
		args[i] = ft_strdup(node->data);
		node = node->right;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	execute_command(t_ast_node *node, t_shell *msh)
{
	char	**args;

	args = init_arguments(node, msh);
	execute_builtin_command(args, msh);
}

void	execute_redirection(t_ast_node *node, t_shell *msh)
{
	if (!node)
		return ;
	if (node->type & NODE_COMMAND)
	{
		execute_command(node, msh);
	}
}

void	execute_pipeline(t_ast_node *node, t_shell *msh)
{
	if (!node)
		return ;
	execute_command(node, msh);

}

void	execute_separator(t_ast_node *node, t_shell *msh)
{
	if (!node)
		return ;
	execute_redirection(node, msh);
}

void execute_syntax_tree(t_ast *syntax_tree, t_shell *msh)
{
	if (!syntax_tree)
		return ;
	execute_separator(syntax_tree->root, msh);
}