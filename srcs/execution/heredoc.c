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
}

int	heredoc_redirect(char	*here_end)
{
	t_pipe		pipe;
	extern int	g_status;

	pipe = init_pipeline(1);
	heredoc_prompt(pipe, here_end);
	close(pipe.fds[1]);
	if (g_status == 130)
	{
		close(pipe.fds[0]);
		return (0);
	}
	return (pipe.fds[0]);
}
