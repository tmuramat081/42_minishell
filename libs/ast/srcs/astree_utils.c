#include "libast.h"

size_t  ast_count_nodes(t_ast_node *root)
{
    if (root == NULL)
        return (0);
    return (1 + ast_count_nodes(root->left) + ast_count_nodes(root->right));
}
