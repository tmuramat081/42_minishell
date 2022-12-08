#include "minishell.h"

void	launch_minishell(void)
{
	char	*line = NULL;

	while (42)
	{
		line = readline("> ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		printf("line is '%s'\n", line);
		add_history(line);
		free(line);
	}
}

int	main(void)
{
	launch_minishell();
	return (0);
}
