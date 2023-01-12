
/**
 * @file parser.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 構文解析のエントリーポイント
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

/**		Backus-Naur Form (BNF)
 *
	<command_line>	::= <pipeline> ';' <command_line>
					|	<pipeline> ';'
					|	<pipeline>

	<pipeline>		::=	<simple_cmd> '|' <pipeline>
					|	<simple_cmd>

	<simple_cmd>	::= cmd_name
					|	cmd_name <cmd_suffix>

	<cmd_suffix>	::= 			 <io_redirect>
					|	<cmd_suffix> <io_redirect>
					|				 word
					|	<cmd_suffix> word

	<io_redirect>	::= '>'  filename
					| 	'>>' filename
					| 	'<'  filename
					| 	'<<' here_end
 *
**/

void	next_token(t_vector *tokens, t_token **curr)
{
	*curr = (t_token *)ft_vector_next(tokens, *curr, 1);;
}

/**
 * @brief 解析対象の文字を取得し、対象を次に移す。
 *
 * @param tokens トークンのリスト
 * @param toketype　判定したいトークンの種別　
 * @param curr　現在解析しているトークン
 * @param buff　正であればbuffにトークンの文字列を書き込む
 * @return true
 * @return false
 */
char *scan_token(t_vector *tokens, t_token **curr)
{
	char *buff;

	if (!curr || !*curr)
		return (NULL);
	buff = ft_strdup((*curr)->data);
	if (!buff)
		return (NULL);
	next_token(tokens, curr);
    return (buff);
}

/**
 * @brief 再帰下降パーサーにより抽象構文木を作成する
 *
 * @param tokens lexerにより分解された各単語
 * @param msh shellのステータスを管理する構造体
 * @return t_ast* 抽象構文木
 */
t_ast_node	*parser(t_vector *tokens, t_shell *msh)
{
	t_ast_node	*syntax_tree;
	t_token		*curr_token;

	(void)msh;
	curr_token = ft_vector_front(tokens);
	syntax_tree = parse_simple_cmd(tokens, &curr_token);
	return (syntax_tree);
}
