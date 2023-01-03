/**
 * @file command.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief 内部・外部コマンドの実行
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"

extern char **environ;

/**
 * @brief 外部コマンドを実行する
 *
 * @param args
 * @param msh
 */
void	execute_external_command(char **args, t_shell *msh)
{
	pid_t	pid;
	char 	*filepath;
	(void)msh;

	filepath = args[1];
	pid = fork();
	if (pid == 0)
	{
		ft_execvpe(args[0], args, construct_environ(msh->envs));
		ft_printf("command not found\n");
		exit (1);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	while (waitpid(pid, NULL, 0) <= 0);
	return ;
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
	else
		execute_external_command(args, msh);
}