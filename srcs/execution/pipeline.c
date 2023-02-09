/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:32:30 by event             #+#    #+#             */
/*   Updated: 2023/02/10 06:15:43 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	xdup2(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) < 0)
			exit(EXIT_FAILURE);
		close(old_fd);
	}
}

void	pipe_update(t_pipe *piped)
{
	int	tmp[2];

	if (pipe(tmp) < 0)
		exit(EXIT_FAILURE);
	piped->reader = tmp[0];
	piped->writer = tmp[1];
}

void	set_pipeline(t_pipe pipe)
{
	if (pipe.state & PIPE_STDIN)
	{
		xdup2(pipe.in_fd, STDIN_FILENO);
	}
	if (pipe.state & PIPE_STDOUT)
	{
		xdup2(pipe.writer, STDOUT_FILENO);
	}
}
