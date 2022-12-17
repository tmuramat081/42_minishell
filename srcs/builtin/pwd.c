#include <libc.h>

void	ft_putendl_fd(char	*s, int	fd)
{
	size_t	i;

	if (!s)
		return ;
	i = 0;
	while (*(s + i) && s[i])
		i++;
	write(fd, s, i * sizeof(char));
	write(fd, "\n", sizeof(char));
}

void	bind_pwd_value(void)
{
	extern char	*g_pwd;

	update_env_value("OLDPWD", get_env_data("PWD"), FALSE, FALSE);
	update_env_value("PWD", g_pwd, FALSE, FALSE);
}

int	main(void)
{
	extern char	*g_pwd;

	ft_putendl_fd(g_pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}