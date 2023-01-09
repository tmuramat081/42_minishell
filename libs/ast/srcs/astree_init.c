#include "libast.h"
#include <stdlib.h>

t_ast   *ast_init()
{
    t_ast   *ast;

    ast = malloc(sizeof(t_ast));
    if (!ast)
        return (NULL);
	*ast = (t_ast){};
	return (ast);
}