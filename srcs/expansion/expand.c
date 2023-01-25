#include "expansion.h"
#include "terminal.h"
#include "libast.h"
/**
 * @brief 抽象構文木を捜査し、コマンドの場合に展開処理を行う。
 *
 * @param node
 * @param msh
 */
void    expand_node(t_ast_node *node, t_shell *msh)
{
    if (!node)
        return ;
    if (node->type & NODE_COMMAND)
    {
        expand_environs(node->command, msh->envs);
    }
    expand_node(node->left, msh);
    expand_node(node->right, msh);
}

/**
 * @brief コマンドラインを展開する。
 *
 * @param syntax_tree
 * @param msh
 */
void    expand(t_ast_node *syntax_tree, t_shell *msh)
{
    expand_node(syntax_tree, msh);
}