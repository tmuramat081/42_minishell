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
	process->fd_backup[0] = dup(STDIN_FILENO);
	process->fd_backup[1] = dup(STDOUT_FILENO);
	process->fd_backup[2] = dup(STDERR_FILENO);
	process->argv = init_arguments(command->arguments);
	process->redirects = command->redirects;
	if (ast_count_redirects(process->redirects) > 0)
		set_redirection(process);
	if (process->reader > 0)
		dup2(process->reader, STDIN_FILENO);
	if (process->writer > 0)
		dup2(process->writer, STDOUT_FILENO);

}

/**
 * @brief 実行処理:コマンド
 *
 * @param node
 * @param msh
 */
void	exec_simple_cmd(t_ast_node *node, t_process process, t_shell *msh)
{
	if (!node || !node->command)
		return ;
	set_command_process(&process, node->command);
	if (is_builtin(process.argv[0]) == true)
		exec_internal_command(process, msh);
	else
		exec_external_command(process, msh);
	reset_redirection(process);
}
