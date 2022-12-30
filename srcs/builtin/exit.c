#include "minishell.h"
#include "libft.h"

void	put_error(char *message, char *arg)
{
	//printf("%s\n", message);
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
	endptr = NULL;
	long_num = ft_strtol_d(arg, &endptr);
	if( (long_num == LONG_MIN || long_num == LONG_MAX) && errno == ERANGE)
		put_error("numeric argument required", arg);
	else if (*endptr || endptr == arg)
		put_error("numeric argument required", arg);
	return ((int)long_num);
}

void builtin_exit(char **args)
{
	size_t	i;
	int		status;

	i = 1;
	size_t res;
	res = ft_matrixlen((const char**)args);
	printf("%zu\n", res);
	if (res > 2)
		put_error("too many arguments", NULL);
	status = input_args(args[i]);
	exit(status);
}