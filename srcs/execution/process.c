/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:24:01 by event             #+#    #+#             */
/*   Updated: 2023/02/08 01:19:37 by tmuramat         ###   ########.fr       */
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
	{
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	wait_all_child_processes(void)
{
	extern int	g_pid;
	extern int	g_status;
	int			status;
	pid_t		pid;

	while (true)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == g_pid)
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
		}
		else if (pid < 0)
			break ;
	}
}

void	wait_child_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}
