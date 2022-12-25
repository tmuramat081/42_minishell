#include "libast.h"

t_ast	ast_init(void)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	return (ast);
}

