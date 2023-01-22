#include "execution.h"

t_pipe pipe_create(void)
{
	t_pipe pipe_fd;
	int		tmp[2];

	pipe_fd = (t_pipe){};
 	if (pipe(tmp) < 0)
	{
		exit(EXIT_FAILURE);
	}
	pipe_fd.reader = tmp[0];
	pipe_fd.writer = tmp[1];
	return (pipe_fd);
}

t_pipe	pipe_init(void)
{
	t_pipe piped;

	piped = (t_pipe){};
	piped.reader = STDIN_FILENO;
	piped.writer = STDOUT_FILENO;
	piped.in_fd = STDIN_FILENO;
	return (piped);
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
	if (pipe.state & PIPE_STDIN)
	{
		dup2(pipe.in_fd, STDIN_FILENO);
		close(pipe.in_fd);
	}
	if (pipe.state & PIPE_STDOUT)
	{
		dup2(pipe.writer, STDOUT_FILENO);
		close(pipe.writer);
	}
}
