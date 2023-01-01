/**
 * @file print_token.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 字句解析デバッグ用のトークン出力
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "ft_printf.h"

char *get_type_name(t_token_type type)
{
	if (type == TOKEN_STR)
		return ("[STRING]");
	else if (type == TOKEN_RDIR)
		return ("[OUTPUT_RDR]");
	else if (type == TOKEN_RRDIR)
		return ("[APPEND_OUTPUT_RDR]");
	else if (type == TOKEN_LDIR)
		return ("[INPUR_RDR]");
	else if (type == TOKEN_LLDIR)
		return ("[HEREDOC_RDR]");
	else if (type == TOKEN_SPACE)
		return ("[SPACE]");
	else if (type == TOKEN_PIPELINE)
		return ("[PIPELINE]");
	else if (type == TOKEN_AMPERSAND)
		return ("[AMPERSAND]");
	else if (type == TOKEN_SEMICOLON)
		return ("[SEMICOLON]");
	else if (type == TOKEN_NULL)
		return ("[EOL]");
	return ("[N/A]");
}

void	print_token(void *p_str, void *p_index)
{
	t_token *token;
	int		*index;
	char	*type;

	index = p_index;
	token = p_str;
	type = get_type_name(token->type);
	ft_printf("[%*d] %*s %*s\n", 2, *index, 20, token->data, 20, type);
	(*index)++;
}

void	print_tokens(t_vector *tokens)
{
	int	index;

	index = 0;
	ft_printf("\n===============================================\n");
	ft_printf("%s %*s %*s\n", "No. ", 20, "TOKEN", 20, "TYPE");
	ft_printf("-----------------------------------------------\n");
	ft_vector_foreach(tokens, print_token, &index);
	ft_printf("===============================================\n");
}