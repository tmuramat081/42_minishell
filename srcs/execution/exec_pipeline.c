#include "execution.h"
#include "libast.h"

/**
 * @brief 実行処理：パイプライン
 *
 * @param node
 * @param msh
 */
void	exec_pipeline(t_ast_node *node, t_shell *msh)
{
	if (!node)
		return ;
	if (node->type & NODE_PIPELINE)
	{
		//TODO: パイプの実装
		return ;
	}
	exec_simple_cmd(node, msh);
}