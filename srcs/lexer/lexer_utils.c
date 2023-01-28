/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:11:48 by event             #+#    #+#             */
/*   Updated: 2023/01/29 01:51:26 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file lexer_utils.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 字句解析のヘルパー関数群
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "terminal.h"
#include "lexer.h"

/**
 * @brief 解析対象の対象を一文字進める。
 *
 * @param tokenizer
 * @return char* 進める前の文字
 */
char	next(t_tokenizer *tk)
{
	char	current;

	if (tk->pos >= ft_strlen(tk->str))
		return ('\0');
	current = tk->str[tk->pos];
	tk->pos += 1;
	return (current);
}

/**　字句解析の対象を一文字戻す。
 * @brief
 *
 * @param tokenizer
 */
void	prev(t_tokenizer *tokenizer)
{
	tokenizer->pos -= 1;
}

/**
 * @brief 現在位置まで文字を切り出し、トークンとして格納する。
 *
 * @param tk
 * @param ttype
 */
void	emit(t_tokenizer *tk, t_token_type token_type)
{
	t_token	*token;

	token = (t_token *)ft_xmalloc(sizeof(t_token));
	if (token_type == TOKEN_END)
		token->data = NULL;
	else
		token->data = ft_substr(tk->str, tk->start, tk->pos - tk->start);
	token->type = token_type;
	format_token(token);
	ft_vector_push_back(tk->tokens, token);
	tk->start = tk->pos;
}

/**
 * @brief 次の解析対象の文字を取得する。
 *
 * @param tokenizer
 * @return char* 次の解析対象にあたる文字
 */
char	peek(t_tokenizer *tokenizer)
{
	char	next_c;

	next_c = next(tokenizer);
	if (next_c != '\0')
		prev(tokenizer);
	return (next_c);
}
