#include "libast.h"

#include <assert.h>
#include <stdlib.h>

void ast_attach_binary_branch(t_ast_node* root, t_ast_node* leftNode, t_ast_node* rightNode)
{
    assert(root);
    root->left = leftNode;
    root->right = rightNode;
}

void ast_tree_set_type(t_ast_node* node, t_node_type type)
{
    assert(node);
    node->type = type;
}

void ast_tree_set_node(t_ast_node* node, char* data)
{
    assert(node);
    if(data != NULL)
    {
        node->szData = data;
        node->type |= NODE_DATA;
    }
}

void ast_node_delete(t_ast_node* node)
{
    if (!node)
        return;
    if (node->type & NODE_DATA)
        free(node->szData);
    ast_node_delete(node->left);
    ast_node_delete(node->right);
    free(node);
}

t_ast   *ast_node_init(t_ast *ast)
{
    t_ast   *ast;

    ast = malloc(sizeof(t_ast));
    if (ast)
        return (NULL);
}