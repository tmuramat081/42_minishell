/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmuramat <tmuramat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 13:10:21 by tmuramat          #+#    #+#             */
/*   Updated: 2023/02/12 13:10:23 by tmuramat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
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
		ft_putendl_fd(line, pipe.fds[1]);
		free(line);
	}
	puts("ONG");
}

int	heredoc_redirect(char	*here_end)
{
	t_pipe	pipe;
	pid_t	pid;

	pipe = init_pipeline(1);
	pipe.state = PIPE_STDOUT;
	pid = create_child_process();
	if (pid == 0)
	{
		set_pipeline(pipe);
		set_ignore_signal();
		xclose(pipe.fds[1]);
		heredoc_prompt(pipe, here_end);
		exit(EXIT_SUCCESS);
	}
	return (pipe.fds[0]);
}
