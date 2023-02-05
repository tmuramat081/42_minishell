/**
 * @file exit.c
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

static int	input_args(char **argv)
{
	char	*endptr;
	long	long_num;

	errno = 0;
	endptr = NULL;
	long_num = ft_strtol_d(argv[1], &endptr);
	if ((long_num == LONG_MIN || long_num == LONG_MAX) \
		&& errno == ERANGE)
	{
		handle_error(MSG_NUM_ARG_REQUIRED, argv[0]);
		return (255);
	}
	else if (*endptr || endptr == argv[1])
	{
		handle_error(MSG_NUM_ARG_REQUIRED, argv[0]);
		return (255);
	}
	return ((int)long_num);
}

int	builtin_exit(char **argv)
{
	size_t 	argc;
	extern	int g_status;

	argc = ft_matrixlen((const char**)argv);
	if (argc > 2)
	{
		handle_error(MSG_TOO_MANY_ARGS, argv[0]);
		exit(1);
	}
	if (argc == 2)
		exit(input_args(argv));
	exit (g_status & 0xFF);
	return (0);
}

