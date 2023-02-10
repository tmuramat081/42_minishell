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

static void	put_error(char *message, char *arg)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
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
		put_error(MSG_NUM_ARG_REQUIRED, NULL);
	else if (*endptr || endptr == argv[1])
		put_error(MSG_NUM_ARG_REQUIRED, NULL);
	return ((int)long_num);
}

int	builtin_exit(char **argv, t_shell *msh)
{
	size_t 		argc;
	extern int	g_status;

	argc = ft_matrixlen((const char **)argv);
	if (argc > 2)
		shell_perror(argv[0], msh);
	if (argc == 2)
		exit(input_args(argv));
	exit (g_status & 0xFF);
	return (0);
}

