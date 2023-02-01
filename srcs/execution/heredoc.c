#include "expansion.h"
#include "execution.h"
#include "constant.h"
#include <readline/readline.h>

void	heredoc_prompt(t_pipe pipe, char *here_end)
{
	char		*line;

	while (true)
	{
		line = readline(HEREDOC_PROMPT);
		if (!line)
			break ;
		else if (ft_strcmp(line, here_end) == 0)
			break ;
		ft_putendl_fd(line, pipe.writer);
		free(line);
	}
}

int	heredoc_redirect(char	*here_end)
{
	t_pipe	pipe;
	pid_t	pid;

	pipe_update(&pipe);
	pid = create_child_process();
	if (pid == 0)
	{
		close_file(pipe.reader);
		heredoc_prompt(pipe, here_end);
		exit(EXIT_SUCCESS);
	}
	wait_child_process(pid);
	close_file(pipe.writer);
	return (pipe.reader);
}
