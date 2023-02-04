/**
 * @file pwd.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - pwdコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "terminal.h"
#include "ft_printf.h"
#include "execution.h"

int	builtin_pwd(char **arg, t_shell *msh)
{
	char	buff[BUFSIZ];

	(void)msh;
	(void)arg;
	if (!getcwd(buff, sizeof(buff)))
		return (-1);
	ft_putendl_fd(buff, STDOUT_FILENO);
	return (0);
}
