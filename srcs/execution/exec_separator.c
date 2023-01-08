#include "execution.h"
#include "libast.h"

/**
 * @brief 実行処理：セパレーター"；"
 * 
 * @param node 
 * @param msh 
 */
void	exec_separator(t_ast_node *node, t_shell *msh)
{
	if (!node)
		return ;
	if (node->type & NODE_SEQUENCE)
	{
		exec_redirect(node->left, msh);
		exec_separator(node->right, msh);
		return ;
	}
	exec_redirect(node, msh);
}