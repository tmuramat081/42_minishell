/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 01:32:30 by event             #+#    #+#             */
/*   Updated: 2023/02/11 03:13:17 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	xdup2(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) < 0)
		{
			close(old_fd);
			exit(EXIT_FAILURE);
		}
	}
}

void	set_pipeline(t_pipe pipes)
{
	if (pipes.state & PIPE_STDOUT)
	{
		xdup2(pipes.fds[pipes.idx + 1], STDOUT_FILENO);
	}
	if ((pipes.state & PIPE_STDIN) && pipes.idx > 1)
	{
		xdup2(pipes.fds[pipes.idx - 2], STDIN_FILENO);
	}
	delete_pipeline(pipes);
}

t_pipe	init_pipeline(size_t cnt)
{
	t_pipe	pipes;
	size_t	i;

	pipes.fds = ft_xmalloc(sizeof(int) * (cnt * 2));
	i = 0;
	while (i < cnt)
	{
		pipe(pipes.fds + i * 2);
		i++;
	}
	pipes.idx = 0;
	pipes.state = 0;
	pipes.len = cnt;
	return (pipes);
}

void	delete_pipeline(t_pipe pipes)
{
	size_t	i;

	i = 0;
	while (i < pipes.len * 2)
	{
		close(pipes.fds[i]);
		i++;
	}
	free(pipes.fds);
}
