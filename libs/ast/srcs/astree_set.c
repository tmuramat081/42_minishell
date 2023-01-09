#include "libast.h"
#include <stdlib.h>

void ast_node_set_type(t_ast_node *node, t_node_type type)
{
	if (!node)
		return ;
    node->type = type;
}

void ast_node_set_data(t_ast_node* node, char *data)
{
	if (!node)
		return ;
	if(data != NULL)
		node->data = data;
}

void	ast_node_set(t_ast_node *node, t_node_type type, char *data)
{
	if (!node)
		return ;
    ast_node_set_type(node, type);
    ast_node_set_data(node, data);
}

