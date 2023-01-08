#include "minishell.h"
#include "execution.h"
#include "libast.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief　コマンド引数ノードから文字列の配列を生成する
 * @detail ast_count_nodesで引数の数を数える
 * @param node
 * @param msh
 * @return char** 引数の配列（[0]はコマンド名）
 */
static char	**init_arguments(t_ast_node *node)
{
	char	**args;
	size_t	i;
    size_t  argc;

    argc = ast_count_nodes(node);
	args = (char **)ft_xmalloc(sizeof(t_ast_node) * argc);
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


/**
 * @brief 実行処理；コマンド
 * 
 * @param node 
 * @param msh 
 */
void	exec_command(t_ast_node *node, t_process process, t_shell *msh)
{
    char **args;

	args = init_arguments(node);
	if (maybe_exec_internal_command(args, process, msh))
    	exec_external_command(args, process, msh);
}


