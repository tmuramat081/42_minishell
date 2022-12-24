#include "minishell.h"
#include "lexer.h"

void	print_token(void *void_str)
{
	t_token *token;

	token = void_str;
	printf("%s\n", token->value);
}
