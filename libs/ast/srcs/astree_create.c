#include "libast.h"
#include <stdlib.h>

void ast_node_create(t_ast_node *root, t_ast_node *lhs, t_ast_node *rhs)
{
	if (!root)
		return ;
    root->left = lhs;
    root->right = rhs;
}