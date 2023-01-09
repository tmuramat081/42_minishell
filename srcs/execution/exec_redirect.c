#include "execution.h"
#include "libast.h"

/**
 * @brief 実行処理：リダイレクト 
 * 
 * @param node 
 * @param msh 
 */
void	exec_redirect(t_ast_node *node, t_shell *msh)
{
    t_process process;

	if (!node)
		return ;
	if (node->type & (NODE_RDIR_INPUT | NODE_RDIR_OUTPUT | NODE_RDIR_APPEND))
	{
		process.redirect_type = node->type;
        process.redirect_file = node->data;
		exec_command(node->right, process, msh);
	}
	else if (node->type & NODE_COMMAND)
	{
        process.redirect_type = node->type;
        process.redirect_file = NULL;
		exec_command(node, process, msh);
	}
}

