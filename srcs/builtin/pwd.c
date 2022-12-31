#include "minishell.h"
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
