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

/**
 * @brief 解析対象の文字を一つ進める。
 *
 * @param tokenizer
 * @return char*
 */
char	next(t_tokenizer *tk)
{
	char current;

	if (tk->pos >= ft_strlen(tk->str))
		return ('\0');
	current = tk->str[tk->pos];
	tk->pos += 1;
	return (current);
}

/**
 * @brief 次の解析対象の文字を取得する。
 *
 * @param tokenizer
 * @return char* 次の解析対象にあたる文字
 */
char	peek(t_tokenizer *tokenizer)
{
	char next_c;

	next_c = next(tokenizer);
	if (next_c != '\0')
		prev(tokenizer);
	return (next_c);
}

/**
 * @brief 現在の解析対象の文字を取得する。
 *
 * @param tokenizer
 * &return char 現在の解析対象にあたる文字
 */
char	current(t_tokenizer *tk)
{
	return (tk->str[tk->pos]);
}

void	prev(t_tokenizer *tokenizer)
{
	tokenizer->pos -= 1;
}


t_token	*format_space(t_token *token)
{
	char *formatted;

	formatted = ft_strtrim(token->data, " ");
	free(token->data);
	token->data = formatted;
	return (token);
}

t_token *format_quote(t_token *token)
{
	char	*formatted;

	if (token->type == TOKEN_STR_SQUOTE)
		formatted = ft_strtrim(token->data, "\'");
	else if (token->type == TOKEN_STR_DQUOTE)
		formatted = ft_strtrim(token->data, "\"");
	else
		formatted = ft_strdup(token->data);
	free(token->data);
	token->data = formatted;
	return (token);
}

void	format_token(t_token *token)
{
	format_space(token);
	format_quote(token);
}

/**
 * @brief 現在位置まで文字を切り出し、トークンとして格納する。
 *
 * @param tk
 * @param ttype
 */
void	emit(t_tokenizer *tk, t_token_type token_type)
{
	t_token *token;

	token = (t_token *)ft_xmalloc(sizeof(t_token));
	token->data = ft_substr(tk->str, tk->start, tk->pos - tk->start);
	token->type = token_type;
	format_token(token);
	if (*token->data)
		ft_vector_push_back(tk->tokens, token);
	tk->start = tk->pos;
}


/**
 * @brief 字句解析のエントリーポイント
 *
 * @param line
 * @return t_vector*
 */
void	lexer(char *line, t_vector **tokens)
{
	t_tokenizer	*tokenizer;
	t_state_fn	next_fn;

	tokenizer = init_tokenizer(line);
	while (tokenizer->state != NULL)
	{
		next_fn = (t_state_fn)tokenizer->state;
		tokenizer->state = next_fn(tokenizer);
	}
	*tokens = tokenizer->tokens;
}
