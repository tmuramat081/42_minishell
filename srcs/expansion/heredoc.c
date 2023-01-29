#include "expansion.h"
#include "execution.h"

void	heredoc_prompt(t_pipe pipe, char *here_end)
{
	const char	*pronpt = "> ";
	char		*line;

	while (true)
	{
		line = readline(pronpt);
		if (!line)
			break ;
		write(pipe.writer, line, ft_strlen(line));
		if (ft_strcmp(line, here_end) == 0)
			break ;
		free(line);
	}
}

int	heredoc_redirect(char	*here_end)
{
	t_pipe	pipe;
	pid_t	pid;

	pipe = pipe_init();
	pid = create_child_process();
	if (pid == 0)
	{
		close(pipe.reader);
		heredoc_prompt(pipe, here_end);
	}
	else
		wait_child_process(pid);
	return (pipe.reader);
}
