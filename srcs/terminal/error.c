#include "terminal.h"

void	handle_error(char *message, char *command)
{
	ft_putstr_fd("m-shell: ", STDERR_FILENO);
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}
