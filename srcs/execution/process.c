/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkohki <kkohki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:24:01 by event             #+#    #+#             */
/*   Updated: 2023/01/31 15:43:12 by kkohki           ###   ########.fr       */
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
	extern int g_status;
	int	status;

	while ((waitpid(-1, &status, 0) > 0))
		;
	if (WIFEXITED(status))
	{
		g_status = WEXITSTATUS(status);
	}
}

void	wait_child_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}