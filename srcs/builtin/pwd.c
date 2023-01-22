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
	char	buf[BUFSIZ];

	(void)msh;
	(void)arg;
	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	return (0);
}
