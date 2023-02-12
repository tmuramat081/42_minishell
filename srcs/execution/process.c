/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:24:01 by event             #+#    #+#             */
/*   Updated: 2023/02/13 00:17:41 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "ft_printf.h"
#include <signal.h>

pid_t	create_child_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	return (pid);
}

void	set_exit_status(int status, bool seen_sigint)
{
	extern int	g_status;
	int			signal;

	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		g_status = signal + 128;
	}
	if (seen_sigint)
		waitpid(-1, &status, 0);
}


void	wait_all_child_processes(size_t cnt)
{
	int		status;
	bool	seen_sigint;

	seen_sigint = false;
	while (cnt)
	{
		waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			seen_sigint = true;
		cnt--;
	}
	set_exit_status(status, seen_sigint);
}

void	wait_child_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}
