#include "expansion.h"
#include "ft_vector.h"
#include "ft_hashmap.h"
#include "terminal.h"

/**
 * @brief コマンドの引数をすべて走査し、 '$'が含まれていれば展開を試みる。
 *
 * @param command
 * @param environ
 */
void	expand_environs(t_command *command, t_hashmap *environ)
{
	t_argument	*curr;
	char		*buff;

	curr = command->arguments;
	while (curr)
	{
		if (curr->type & NODE_WORD)
		{
			buff = NULL;
			ft_wordexp(curr->argument, &buff, environ);
			free(curr->argument);
			curr->argument = ft_strdup(buff);
		}
		curr = curr->next;
	}
}
