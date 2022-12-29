#include <fcntl.h>
#include "lexer.h"
#include "minishell.h"
#include "parser.h"

#define DOT_FILE_NAME	"ast.dot"
#define DOT_INDENT		"    "

void	print_edge(t_ast_node *left, t_ast_node *right, int fd)
{
	ft_putstr_fd(DOT_INDENT"NODE_", fd);
	ft_putstr_fd(" -> NODE_", fd);
	ft_putendl_fd(";", fd);
}

/*
** print node and edge definitions
**     NODE_{node} [label="{node->type}\n{args}\n{redirects}"];
**     NODE_{node} -> NODE_{node->left;}
**     NODE_{node} -> NODE_{node->right;}
*/

void	print_node(t_ast_node *node, int fd)
{
	ft_putstr_fd(DOT_INDENT"NODE_", fd);
	if (node->left)
	{
		print_edge(node, node->left, fd);
	}
	if (node->right)
	{
		print_edge(node, node->right, fd);
	}
}

void	print_nodes_rec(t_ast_node *node, int fd)
{
	if (!node)
		return ;
	print_node(node, fd);
	print_nodes_rec(node->left, fd);
	print_nodes_rec(node->right, fd);
}

void	print_nodes(t_ast_node *node)
{
	int	fd;

	printf("digraph AST {\n");
	print_nodes_rec(node, fd);
	ft_putstr_fd("}\n", fd);
}