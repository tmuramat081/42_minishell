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

/**
 * @brief ビルトイン関数群
 * 
 */
static const t_builtin g_builtins[8] = {
	{"echo", &builtin_echo},
	{"cd", &builtin_cd},
	{"pwd", &builtin_pwd},
	{"export", &builtin_export}, 
	{"unset", &builtin_unset},
	{"env", &builtin_env},
	{"exit", &builtin_exit},
	{NULL, NULL},
};

void	reset_redirection(t_process process)
{
	(void)process;
	return ;
}

/**
 * @brief 内部コマンドを実行する
 *
 * @param args　コマンドの引数（0番目はプログラム名）
 * @param msh シェルの管理情報
 */
int		maybe_exec_internal_command(char **args, t_process process, t_shell *msh)
{
	size_t	i;

	int fd_backup = dup(STDOUT_FILENO);
	if (process.redirect_file)
		set_redirection(process);
	i = 0;
	while (g_builtins[i].symbol)
	{
		if (!ft_strcmp(args[0], g_builtins[i].symbol))
			return (g_builtins[i].func(args, msh));
		i++;
	} 
	dup2(STDOUT_FILENO, fd_backup);
	close(fd_backup);
	reset_redirection(process);
	return (1);
}