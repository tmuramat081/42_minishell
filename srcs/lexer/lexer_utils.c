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

bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '&' || c == '<'
		|| c == '>' || c == '|' || c == ';')
		return (true);
	return (false);
}

bool	is_quotation(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}