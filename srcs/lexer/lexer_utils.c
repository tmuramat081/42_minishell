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
 * @brief 字句解析器の構造体を初期化する
 *
 * @param line　解析したい文字列
 * @return t_tokenizer*　字句解析器の構造体
 */
t_tokenizer	*init_tokenizer(char *line)
{
	t_tokenizer	*tokenizer;

	tokenizer = malloc(sizeof(t_tokenizer));
	tokenizer->str = line;
	tokenizer->pos = line;
	tokenizer->state = STATE_NORMAL;
	return (tokenizer);
}

/**
 * @brief 字句解析器の構造体を解放する
 *
 * @param tokenizer
 */
void	delete_tokenizer(t_tokenizer *tokenizer)
{
	free(tokenizer);
}

/**
 * @brief メタキャラクターの判定
 *
 * @param c　判定したい文字
 * @return true　メタキャラクターである
 * @return false　メタキャラクターでない
 */
bool	is_metacharacter(char c)
{
	if (c == ' ' || c == '\t' || c == '&' || c == '<'
		|| c == '>' || c == '|' || c == ';')
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
bool	is_quotation(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}