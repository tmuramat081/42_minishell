#include "ft_hashmap.h"
#include "terminal.h"


/**
 * @file cd.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - cdコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "execution.h"

int	builtin_cd(char **args, t_shell *msh)
{
	char *path;

	if (!args || !*args)
		return (1);
	if (!args[1])
		path = ft_getenv("HOME", msh->envs);
	else
		path = args[1];
	if (chdir(path))
	{
		ft_putendl_fd("error", 2);
		return (+1);
	}
	return (0);
}
