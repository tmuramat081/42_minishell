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
	else if (c == '' )
	return (false);
}

void	handle_state(t_tokenizer *tk)
{
	if (!*tk->pos)
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
	if (is_metacharacter(*startptr) == true)
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
		if (is_delimiter(tokenizer, *(endptr + 1)))
		{
			token = ft_strndup(startptr, (endptr - startptr) + 1);
			tokenizer->pos = endptr + 1;
			while (ft_isspace(*tokenizer->pos))
				tokenizer->pos++;
			return (token);
		}
		endptr++;
	}
	return (NULL);
}

void	tokenizer(char *line)
{
	t_tokenizer	*tk;
	char		*token;

	tk = init_tokenizer(line);
	while (true)
	{
		handle_state(tk);
		token = get_next_token(tk);
		if (!token)
			break ;
		ft_vector_push_back(tk->tokens, token);
		free(token);
	}
	ft_vector_foreach(tk->tokens, print_token);
	delete_tokenizer(tk);
}
