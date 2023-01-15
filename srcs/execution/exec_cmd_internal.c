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

bool	is_builtin(char *args)
{
	size_t i;

	i = 0;
	while (g_builtins[i].symbol)
	{
		if (!ft_strcmp(args, g_builtins[i].symbol))
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief 内部コマンドを実行する
 *
 * @param args　コマンドに渡す引数の配列（[0]はコマンド名）
 * @param msh シェルの管理情報
 * @return int 実行したコマンドの戻り値を返す。コマンドが見つからなければ1を返す。
 */
int		exec_internal_command(t_process process, t_shell *msh)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].symbol)
	{
		if (!ft_strcmp(process.argv[0], g_builtins[i].symbol))
			return (g_builtins[i].func(process.argv, msh));
		i++;
	}
	return (1);
}