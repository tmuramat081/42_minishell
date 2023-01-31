#include "expansion.h"
#include "terminal.h"
#include "libast.h"

/**
 * @brief コマンドの引数をすべて走査し、 単語の展開を試みる。
 *
 * @param command
 * @param environ
 */
static void	expand_word(t_command *command, t_hashmap *environ)
{
	t_argument	*curr;
	char		*buff;

	curr = command->arguments;
	while (curr)
	{
		if (curr->type & NODE_WORD)
		{
			buff = NULL;
			ft_wordexp(curr->argument, &buff, environ);
			free(curr->argument);
			curr->argument = ft_strdup(buff);
		}
		curr = curr->next;
	}
}

/**
* @brief 抽象構文木の各ノードを走査し、それがコマンドである場合は展開を試みる。
 *
 * @param node
 * @param msh
 */
static void	expand_node(t_ast_node *node, t_shell *msh)
{
	if (!node)
		return ;
	if (node->type & NODE_COMMAND)
	{
		expand_word(node->command, msh->envs);
	}
	expand_node(node->left, msh);
	expand_node(node->right, msh);
}

/**
 * @brief コマンドラインの文字列を展開する。
 *
 * @param syntax_tree
 * @param msh
 */
void	expander(t_ast_node *syntax_tree, t_shell *msh)
{
	expand_node(syntax_tree, msh);
}
