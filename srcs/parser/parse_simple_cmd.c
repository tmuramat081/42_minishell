#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

// <redirect>
static t_ast_node *parse_redirect1(t_vector *tokens, t_token **curr)
{
 	return (parse_redirect_io(tokens, curr));
}

// <redirect> <simple_command>
static t_ast_node *parse_redirect2(t_vector *tokens, t_token **curr)
{
	t_ast_node	*lhs_node;
	t_ast_node	*rhs_node;
	t_ast_node	*node;

    lhs_node = parse_redirect_io(tokens, curr);
    if (!lhs_node)
        return (NULL);
    rhs_node = parse_redirect(tokens, curr);
    if (!rhs_node)
        return (NULL);
	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_REDIRECT, NULL);
	ast_attach_binary_branch(node, lhs_node, rhs_node);
	return (node);
}

// <command>
static t_ast_node *parse_redirect3(t_vector *tokens, t_token **curr)
{
	return (parse_command(tokens, curr));
}
// <io_file> <word> <cmd_suffix>
static t_ast_node *parse_simple_cmd(t_vector *tokens, t_token **curr)
{
	t_ast_node	*lhs_node;
	t_ast_node	*rhs_node;
	t_ast_node	*node;

    lhs_node = parse_io_file(tokens, curr);
    if (!lhs_node)
        return (NULL);
    node = parse_word(tokens, curr);
    if (!rhs_node)
        return (NULL);
    rhs_node = parse_cmd_suffix(tokens, curr);
    if (!rhs_node)
        return (NULL);
	ast_node_set(node, NODE_REDIRECT, NULL);
	ast_attach_binary_branch(node, lhs_node, rhs_node);
	return (node);
}

/**
 * @brief  リダイレクトの解析
 *
 * @param tokens
 * @param curr
 * @return t_ast_node*
 */
t_ast_node  *parse_simple_cmd(t_vector *tokens, t_token **curr)
{
    t_token     *save;
    t_ast_node  *node;

    puts("REDIRECT");
    save = *curr;
    node = parse_simple_cmd1(tokens, curr);
    if (node)
        return (node);
    save = *curr;
    node = parse_simple_cmd2(tokens, curr);
    if (node)
        return (node);
    save = *curr;
    node = parse_simple_cmd3(tokens, curr);
    if (node)
        return (node);
    save = *curr;
    node = parse_simple_cmd4(tokens, curr);
    if (node)
        return (node);
    save = *curr;
    node = parse_simple_cmd5(tokens, curr);
    if (node)
        return (node);
    return (NULL);
}