#include "libast.h"
#include <stdlib.h>

void ast_node_delete(t_ast_node *node)
{
    if (!node)
        return;
    if (node->data)
        free(node->data);
	ast_node_delete(node->left);
	ast_node_delete(node->right);
	free(node);
}

void		ast_delete(t_ast **ast)
{
    free(*ast);
    *ast = NULL;
}