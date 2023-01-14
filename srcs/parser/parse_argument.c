/**
 * @file parse_argument.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析その5：引数 ex."-n", "hello"
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

/**
 * @note
 * [BNF]
 * <word> := word
 * [EBNF]
 * word := 'word'
 */

/**
 * @brief 引数の解析
 *
 * @param tokens
 * @param curr
 * @return t_argument*
 */
t_argument	*parse_argument(t_vector *tokens, t_token **curr)
{
	char		*arg;

	arg = scan_token(tokens, curr);
	return(ast_argument_create(arg));
}

