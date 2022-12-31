#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"


void	execute_external_command(char **args, t_shell *msh)
{
	(void)args;
	(void)msh;
}

/**
 * @brief 内部コマンドを実行する
 *
 * @param args　コマンドの引数（0番目はプログラム名）
 * @param msh シェルの管理情報
 */
void	execute_builtin_command(char **args, t_shell *msh)
{
	if (!ft_strcmp(args[0], "echo"))
		builtin_echo(args, msh);
	else if (!ft_strcmp(args[0], "env"))
		builtin_env(args, msh);
	else if (!ft_strcmp(args[0], "export"))
		builtin_export(args, msh);
	else if (!ft_strcmp(args[0], "unset"))
		builtin_unset(args, msh);
	else if (!ft_strcmp(args[0], "cd"))
		builtin_cd(args, msh);
	else if (!ft_strcmp(args[0], "pwd"))
		builtin_pwd(args, msh);
	else if (!ft_strcmp(args[0], "exit"))
		builtin_exit(args, msh);
	execute_external_command(args, msh);

}