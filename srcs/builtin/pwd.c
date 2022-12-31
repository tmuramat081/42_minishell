#include "minishell.h"

int	pwd(char **arg, t_hashmap *map)
{
	char	buf[BUFSIZ];
	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	return (0);
}
