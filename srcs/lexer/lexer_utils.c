#include "minishell.h"
#include "lexer.h"

t_tokenizer	*init_tokenizer(char *line)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	tokenizer->str = line;
	tokenizer->pos = line;
	tokenizer->state = STATE_NORMAL;
	return (tokenizer);
}

void	delete_tokenizer(t_tokenizer *tokenizer)
{
	free(tokenizer);
}
