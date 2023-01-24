#include "execution.h"
#include "ft_printf.h"
#include <signal.h>

pid_t	create_child_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		exit(EXIT_FAILURE);
	}
//	else if (pid > 0)
//		ft_printf("create process:%d\n", (int)pid);
	return (pid);
}

void	wait_all_child_processes()
{
	int		status;

	while((wait(&status) > 0));
}

void	wait_child_process(pid_t pid)
{
	int		status;

    waitpid(pid, &status, 0);
}

