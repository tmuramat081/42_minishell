/**
 * @file execute.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 抽象構文木を操作し実行処理に渡す
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "libast.h"
#include "parser.h"
#include "minishell.h"
#include "execution.h"

/**
 * @brief　コマンド引数ノードから文字列の配列を生成
 * @detail TODO:メモリ確保は現状決め打ち
 * @param node
 * @param msh
 * @return char**
 */
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
	if (node->type & NODE_SEQUENCE)
	{
		execute_redirection(node->left, msh);
		execute_separator(node->right, msh);
		return ;
	}
	execute_redirection(node, msh);
}

void execute_syntax_tree(t_ast *syntax_tree, t_shell *msh)
{
	if (!syntax_tree)
		return ;
	execute_separator(syntax_tree->root, msh);
}