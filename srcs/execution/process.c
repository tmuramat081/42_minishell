/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:24:01 by event             #+#    #+#             */
/*   Updated: 2023/01/27 01:34:39 by event            ###   ########.fr       */
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

void	wait_all_child_processes()
{
	int	status;

	while ((wait(&status) > 0));
}

void	wait_child_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
}

// l26: else if (pid > 0)
// l27:	ft_printf("create process:%d\n", (int)pid);