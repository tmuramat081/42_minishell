/**
 * @file print_tree.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析デバッグ用のAST出力
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <fcntl.h>
#include "lexer.h"
#include "minishell.h"
#include "parser.h"
#include "ft_printf.h"

#define INDENT "    "

char	*get_node_type(t_node_type	type)
{
	if (type & NODE_PIPELINE)
		return("[PIPELINE]");
	else if (type & NODE_SEQUENCE)
		return("[SEQUENCE]");
	else if (type & NODE_RDIR_INPUT)
		return("[RDIR_INPUT]");
	else if (type & NODE_RDIR_OUTPUT)
		return("[RDIR_OUTPUT]");
	else if (type & NODE_RDIR_APPEND)
		return("[RDIR_APPEND]");
	else if (type & NODE_RDIR_HEREDOC)
		return("[RDIR_HEREDOC]");
	else if (type & NODE_COMMAND)
		return("[COMMAND]");
	else if (type & NODE_ARGUMENT)
		return("[ARGUMENT]");
	else if (type & NODE_FILENAME)
		return("[FILENAME]");
	return ("[N/A]");
}

void	print_arg(void *p_arg)
{
	char *arg = p_arg;
	ft_printf("%s \n", arg);
}

void	print_redirect(void *p_redirect)
{
	t_redirect *redirect;

	redirect = p_redirect;
	ft_printf("%s ", redirect->file);
}

void	print_node_command(void *p_command)
{
	t_command *cmd;

	cmd = (t_command *)p_command;
	ft_deque_foreach(cmd->arg, print_arg);
	ft_deque_foreach(cmd->redirect, print_redirect);
}


void	print_indent(int depth)
{
	while (depth--)
		ft_printf("%s", INDENT);
}

void	print_node(t_ast_node *node)
{
	ft_printf("-");
	ft_printf("%s ", get_node_type(node->type));
	if (node->type & NODE_COMMAND)
		print_node_command(node->data);
}

void	print_nodes_rec(t_ast_node *node, int depth)
{
	if (!node)
		return ;
	print_nodes_rec(node->left, depth + 1);
	print_indent(depth);
	print_node(node);
	print_nodes_rec(node->right, depth + 1);
}

void	print_nodes(t_ast_node *node)
{
	ft_printf("\n%s>>>> PARSER >>>>", GREEN);
	ft_printf("\n===============================================\n");
	print_nodes_rec(node, 0);
	ft_printf("===============================================%s\n\n", DEFAULT);
}