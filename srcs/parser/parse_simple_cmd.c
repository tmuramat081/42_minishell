#include "parser.h"
#include "lexer.h"
#include "libast.h"
#include "minishell.h"

// <io_redirect>
static t_ast_node *parse_simple_cmd2(t_vector *tokens, t_token **curr)
{
	return (parse_redirect(tokens, curr));
}

// <io_redirect> <simple_cmd>
static t_ast_node *parse_simple_cmd1(t_vector *tokens, t_token **curr)
{
	t_ast_node	*rhs_node;
	t_ast_node	*node;

    return (NULL);
    rhs_node = parse_redirect(tokens, curr);
    if (!rhs_node)
        return (NULL);
    rhs_node = parse_simple_cmd(tokens, curr);
    if (!rhs_node)
    {
        ast_node_delete(rhs_node);
        return (NULL);
    }
 	node = ft_xmalloc(sizeof(t_ast_node));
	ast_node_set(node, NODE_FILENAME, NULL);
	ast_node_create(node, NULL, rhs_node);
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

    puts("start:simple_cmd");
    save = *curr;
    node = parse_simple_cmd1(tokens, curr);
    if (node)
        return (node);
    save = *curr;
    node = parse_simple_cmd2(tokens, curr);
    if (node)
        return (node);
    puts("end:simple_cmd");
    return (NULL);
}