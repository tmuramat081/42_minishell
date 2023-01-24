/**
 * @file exit.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief ビルトイン - exitコマンド
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "terminal.h"

void	put_error(char *message, char *arg)
{
	int fd = 0;
	ft_putstr_fd("exit: ", fd);
	if (arg)
		ft_putstr_fd(arg, fd);
	ft_putendl_fd(message, fd);
	exit(255);
}

int	input_args(char *arg)
{
	char	*endptr;
	long	long_num;

	errno = 0;
	if (!arg)
		return (0);
	endptr = NULL;
	long_num = ft_strtol_d(arg, &endptr);
	if( (long_num == LONG_MIN || long_num == LONG_MAX) && errno == ERANGE)
		put_error("numeric argument required", arg);
	else if (*endptr || endptr == arg)
		put_error("numeric argument required", arg);
	return ((int)long_num);
}

void	builtin_exit(char **argv)
{
	size_t	i;
	int		status;
	size_t 	argc;

	i = 1;
	argc = ft_matrixlen((const char**)argv);
	if (argc > 2)
		put_error("too many arguments", NULL);
	status = input_args(argv[i]);
	exit(status);
}

