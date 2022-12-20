#include "minishell.h"
#include "lexer.h"

void	print_token(void *void_str)
{
	char *str = void_str;
	printf("%s\n", str);
}
