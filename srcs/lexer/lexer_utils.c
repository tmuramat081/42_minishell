/**
 * @file lexer_utils.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 字句解析のヘルパー関数
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "minishell.h"
#include "lexer.h"

/**
 * @brief 字句解析器の管理情報を初期化する。
 *
 * @param line　解析したい文字列
 * @return t_tokenizer*　字句解析器の構造体
 */
t_tokenizer	*init_tokenizer(char *line)
{
	t_tokenizer	*tokenizer;

	tokenizer = ft_xmalloc(sizeof(t_tokenizer));
	tokenizer->start = line;
	tokenizer->pos = line;
	tokenizer->state = lex_general;
	tokenizer->tokens = ft_vector_init(sizeof(t_token), 32);
	if (!tokenizer->tokens)
		return (NULL);
	return (tokenizer);
}

/**
 * @brief 字句解析器の構造体を削除する
 *
 * @param tokenizer
 */
void	delete_tokenizer(t_tokenizer *tokenizer)
{
	ft_vector_delete(&tokenizer->tokens);
	free(tokenizer);
}

bool	ft_isquote(int c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

bool	ft_isnull(int c)
{
	if (c == '\0')
		return(true);
	return (false);
}

/**
 * @brief メタキャラクターの判定
 *
 * @param c　判定したい文字
 * @return true　メタキャラクターである
 * @return false　メタキャラクターでない
 */
bool	is_metacharacter(int c)
{
	if (c == ' ' || c == '\t' || c == '&' || c == '<'
		|| c == '>' || c == '|' || c == ';')
		return (true);
	return (false);
}

bool	is_redirection(int c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_delimiter(int c)
{
	if (ft_isspace(c) || ft_isquote(c) || ft_isnull(c)
		|| is_redirection(c) || c == '|' || c == ';')
		return (true);
	return (false);
}

/**
 * @brief （ダブル）クオーテーションの判定
 *
 * @param c
 * @return true （ダブル）クオーテーションである
 * @return false　（ダブル）クオーテーションでない
 */
bool	is_quotation(int c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}