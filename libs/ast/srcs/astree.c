#include "libast.h"

#include <assert.h>
#include <stdlib.h>

void ast_attach_binary_branch(t_ast_node* root, t_ast_node* leftNode, t_ast_node* rightNode)
{
	if (!root)
		return ;
    root->left = leftNode;
    root->right = rightNode;
}

void ast_node_set_type(t_ast_node* node, t_node_type type)
{
	if (!node)
		return ;
    node->type = type;
}

void ast_node_set_data(t_ast_node* node, char* data)
{
    if (!node)
		return ;
    if(data != NULL)
    {
        node->data = data;
        node->type |= NODE_DATA;
    }
}

void ast_node_delete(t_ast_node *node)
{
    if (!node)
        return;
    if (node->type & NODE_DATA)
        free(node->data);
	ast_node_delete(node->left);
	ast_node_delete(node->right);
	free(node);
}

t_ast   *ast_init()
{
    t_ast   *ast;

    ast = malloc(sizeof(t_ast));
    if (!ast)
        return (NULL);
	*ast = (t_ast){};
	return (ast);
}