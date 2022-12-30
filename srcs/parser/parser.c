#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

/**
* @file parser.c
* @brief 構文解析（パーサー）のエントリーポイント
* @author tmuramat
* @date 2022.12.30
*/

/**
 * @brief 解析しているトークンの種類が一致するか判定し、次のトークンを取得する
 *
 * @param tokens トークンのリスト
 * @param toketype　判定したいトークンの種別　
 * @param curr　現在解析しているトークン
 * @param buff　正であればbuffにトークンの文字列を書き込む
 * @return true
 * @return false
 */
bool term(t_vector *tokens, t_token_type toketype, t_token **curr, char **buff)
{
	if (!curr || !*curr)
		return (false);
    if ((*curr)->type == toketype)
    {
		if (buff)
			*buff = ft_strdup((*curr)->data);
		*curr = (t_token *)ft_vector_next(tokens, *curr, 1);
        return (true);
    }
	*curr = (t_token *)ft_vector_next(tokens, *curr, 1);;
    return (false);
}

/**
 * @brief 再帰下降パーサーにより抽象構文木を作成する
 *
 * @param tokens lexerにより分解された各単語
 * @param msh shellのステータスを管理する構造体
 * @return t_ast* 抽象構文木
 */
t_ast	*parser(t_vector *tokens, t_shell *msh)
{
	t_ast	*syntax_tree;
	t_token	*curr_token;

	(void)msh;
	curr_token = ft_vector_front(tokens);
	syntax_tree = ast_init();
	syntax_tree->ast = parse_command_line(tokens, curr_token);
	if (DEBUG)
		print_nodes(syntax_tree);
	return (syntax_tree);
}
