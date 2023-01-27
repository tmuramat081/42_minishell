/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:32:30 by event             #+#    #+#             */
/*   Updated: 2023/01/27 01:32:31 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_pipe	pipe_init(void)
{
	t_pipe	piped;

	piped = (t_pipe){};
	piped.reader = STDIN_FILENO;
	piped.writer = STDOUT_FILENO;
	piped.in_fd = STDIN_FILENO;
	return (piped);
}

void	pipe_update(t_pipe *piped)
{
	int	tmp[2];

	if (pipe(tmp) < 0)
	{
		exit(EXIT_FAILURE);
	}
	piped->reader = tmp[0];
	piped->writer = tmp[1];
}

void	pipe_fd_backup(t_pipe *pipe)
{
	pipe->backup[0] = dup(STDIN_FILENO);
	pipe->backup[1] = dup(STDOUT_FILENO);
}

void	pipe_fd_restore(t_pipe pipe)
{
	dup2(pipe.backup[0], STDIN_FILENO);
	dup2(pipe.backup[1], STDOUT_FILENO);
}

void	set_pipeline(t_pipe pipe)
{
	if (pipe.state & PIPE_STDOUT)
		close_file(pipe.reader);
	if (pipe.state & PIPE_STDIN && pipe.in_fd != STDIN_FILENO)
	{
		dup2(pipe.in_fd, STDIN_FILENO);
		close(pipe.in_fd);
	}
	if (pipe.state & PIPE_STDOUT && pipe.in_fd != STDOUT_FILENO)
	{
		dup2(pipe.writer, STDOUT_FILENO);
		close_file(pipe.writer);
	}
}
