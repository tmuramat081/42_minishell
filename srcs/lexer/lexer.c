/**
 * @file lexer.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 字句解析のエントリーポイント
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "minishell.h"
#include "lexer.h"

#define INIT_SIZE 36

bool	is_delimiter(t_tokenizer *tokenizer, char c)
{
	if (c == '\0')
		return (true);
	else if (is_metacharacter(c) == true && tokenizer->state == STATE_NORMAL)
	{
		return (true);
	}
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

/**
 * @brief 字句解析のエントリーポイント
 *
 * @param line
 * @return t_vector*
 */
t_vector	*lexer(char *line)
{
	t_tokenizer	*tokenizer;
	t_token		*token;
	t_vector	*tokens;

	tokens = ft_vector_init(sizeof(t_token), 16);
	tokenizer = init_tokenizer(line);
	while (true)
	{
		handle_state(tokenizer);
		token = ft_xmalloc(sizeof(t_token));
		token->data = get_next_token(tokenizer);
		if (!token->data || !*token->data)
			break ;
		token->type = get_token_type(token->data);
		ft_vector_push_back(tokens, token);
		token = NULL;
	}
	if (DEBUG)
		print_tokens(tokens);
	return (tokens);
}
