#include "minishell.h"
#include "execution.h"
#include "libast.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief　コマンド引数のリストから文字列の配列を生成する。
 *
 * @details ast_count_nodesで引数の数を数える
 * @param node
 * @param msh
 * @return char** コマンド引数の配列（[0]にはコマンド名が入る）
 */
static char	**init_arguments(t_argument *arguments)
{
	char	**argv;
	size_t	i;
    size_t  argc;

    argc = ast_count_arguments(arguments);
	argv = (char **)ft_xmalloc(sizeof(t_ast_node) * (argc + 1));
	i = 0;
	while (arguments)
	{
		argv[i] = ft_strdup(arguments->argument);
		arguments = arguments->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

/**
 * @brief コマンド実行プロセスを初期化する。
 *
 * @details 引数・リダイレクト・パイプの設定を行う。
 * @param command
 * @return t_process*
 */
static void set_command_process(t_process *process, t_command *command)
{
	process->argv = init_arguments(command->arguments);
	process->redirects = command->redirects;
}

/**
 * @brief 実行処理:コマンド
 *
 * @param node
 * @param msh
 */
void	exec_simple_cmd(t_ast_node *node, t_process process, t_shell *msh)
{
	t_builtin_fn *builtin_command;

	if (!node)
		return ;
	puts(ast_get_command_name(node->command));
	set_command_process(&process, node->command);
	builtin_command = search_builtin(process.argv[0]);
	if (builtin_command)
		(*builtin_command)(process.argv, msh);
	else
		exec_external_command(process, msh);
}
