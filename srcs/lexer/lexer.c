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
char	next(t_tokenizer *tokenizer)
{
	puts("NEXT");
	char next_c;

	if (*(tokenizer->pos) == CHAR_NULL)
		return ('\0');
	next_c = *tokenizer->pos;
	tokenizer->pos += 1;
	return (next_c);
}

/**
 * @brief 次の解析対象の文字を取得する。
 *
 * @param tokenizer
 * @return char*
 */
char	peek(t_tokenizer *tokenizer)
{
	puts("PEEK");
	char next_c;

	next_c = next(tokenizer);
	if (next_c != '\0')
		tokenizer->pos -= 1;
	return (next_c);
}

/**
 * @brief 現在位置まで文字を切り出し、トークンとして格納する
 *
 * @param tk
 * @param ttype
 */
void	emit(t_tokenizer *tk, t_token_type token_type)
{
	puts("EMIT");
	t_token *token;

	token = (t_token *)ft_xmalloc(sizeof(t_token));
	token->data = ft_strndup(tk->start, tk->pos - tk->start);
	token->type = token_type;
	printf("->[%s]\n", token->data);
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
