#include "minishell.h"
#include "lexer.h"

#define INIT_SIZE 36

bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '&' || c == '<'
		|| c == '>' || c == '|' || c == ';')
		return (true);
	return (false);
}

bool	is_delimiter(t_tokenizer *tokenizer, char c)
{
	if (c == '\0')
		return (true);
	else if (is_metacharacter(c) == true && tokenizer->state == STATE_NORMAL)
		return (true);
	return (false);
}

void	handle_state(t_tokenizer *tk)
{
	if (*tk->pos == '\0')
		tk->state = STATE_NORMAL;
	else if (tk->state == STATE_NORMAL)
	{
		if (*tk->pos == '\'')
			tk->state = STATE_SINGLE_QUOTE;
		else if (*tk->pos == ('\"'))
			tk->state = STATE_DOUBLE_QUOTE;
	}
	else if (tk->state == STATE_SINGLE_QUOTE && *tk->pos == '\'')
		tk->state = STATE_NORMAL;
	else if (tk->state == STATE_DOUBLE_QUOTE && *tk->pos == '\"')
		tk->state = STATE_NORMAL;
}

char	*get_next_token(t_tokenizer *tokenizer)
{
	char	*startptr;
	char	*endptr;
	char	*token;

	startptr = tokenizer->pos;
	if (tokenizer->pos == '\0')
		return (NULL);
	if (is_delimiter(tokenizer, *startptr) == true)
	{
		if (*startptr == '\0')
			return (NULL);
		token = ft_strndup(startptr, 1);
		tokenizer->pos++;
		return (token);
	}
	if (*startptr == '\0')
		return (NULL);
	endptr = startptr;
	while (true)
	{
		if (is_delimiter(tokenizer, *endptr) == true)
		{
			token = ft_strndup(startptr, endptr - startptr);
			tokenizer->pos = endptr;
			while (ft_isspace(*tokenizer->pos))
				tokenizer->pos++;
			return (token);
		}
		endptr++;
	}
	return (NULL);
}

t_vector	*tokenizer(char *line)
{
	t_tokenizer	*tokenizer;
	t_token		*token;
	t_vector	*tokens;

	tokens = ft_vector_init(sizeof(t_token), 16);
	tokenizer = init_tokenizer(line);
	while (true)
	{
		token = malloc(sizeof(t_token));
		token->value = get_next_token(tokenizer);
		if (!token->value || !*token->value)
			break ;
		ft_vector_push_back(tokens, token);
		token->value = NULL;
	}
	return (tokens);
//	delete_tokenizer(tk);
}
