#include "libast.h"
#include <stdlib.h>

void ast_node_set_type(t_ast_node *node, t_node_type type)
{
	if (!node)
		return ;
    node->type = type;
}
