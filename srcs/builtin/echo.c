#include "minishell.h"
#include "ft_printf.h"

int	is_n_option(const char *s)
{
	if (ft_strncmp(s, "-n", 2))
		return (0);
	s++;
	while (*s == 'n')
		s++;
	if (!(*s))
		return (1);
	return (0);
}

int	builtin_echo(const char **args, t_shell *msh)
{
	size_t	i;
	size_t	len;
	bool	not_work;

	(void)msh;
	len = ft_matrixlen(args);
	if (len == 1)
	{
		ft_printf("\n");
		return (0);
	}
	i = 1;
	not_work = false;
	while (args[i] && is_n_option(args[i]))
	{
		not_work = true;
		i++;
	}
	while (i < len)
	{
		ft_printf("%s", args[i]);
		i++;
		if (i < len)
			ft_printf(" ");
	}
	if (not_work == false)
		ft_printf("\n");
	return (0);
}
