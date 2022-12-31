#include "minishell.h"
#include "ft_printf.h"

int	pwd(char **arg, t_hashmap *map)
{
	char	buf[BUFSIZ];

	(void)map;
	if (getcwd(buf, sizeof(buf)) != NULL)
		ft_printf("%s\n", buf);
	return (0);
}
