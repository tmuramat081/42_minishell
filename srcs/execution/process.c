#include "execution.h"
#include <signal.h>

pid_t	create_child_process(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	wait_all_child_processes(void)
{
	int		status;

    while (waitpid(-1, &status, 0) <= 0);
}

void	wait_child_process(pid_t pid)
{
	int		status;

    waitpid(pid, &status, 0);
}

