#include <fcntl.h>
#include "lexer.h"
#include "minishell.h"
#include "parser.h"

#define DOT_FILE_NAME	"ast.dot"
#define DOT_INDENT		"    "

void	print_edge(t_ast_node *left, t_ast_node *right)
{
	(void)left;
	(void)right;
//	printf(DOT_INDENT"NODE_");
//	printf(" -> NODE_");
//	printf(";");
}

void	print_node(t_ast_node *node)
{
	printf("%s\n", node->data);
	if (node->left)
	{
		print_edge(node, node->left);
	}
	if (node->right)
	{
		print_edge(node, node->right);
	}
}

void	print_nodes_rec(t_ast_node *node)
{
	if (!node)
		return ;
	print_node(node);
	print_nodes_rec(node->left);
	print_nodes_rec(node->right);
}

void	print_nodes(t_ast *ast)
{
	print_nodes_rec(ast->ast);
	printf("============================\n");
}