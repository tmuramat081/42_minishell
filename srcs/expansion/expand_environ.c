#include "expansion.h"
#include "ft_vector.h"
#include "ft_hashmap.h"
#include "terminal.h"

/**
 * @brief コマンドの引数をすべて捜査し、環境変数が含まれていれば展開する。
 *
 * @param command
 * @param environ
 */
void    expand_environs(t_command *command, t_hashmap *environ)
{
    t_argument *curr;

    curr = command->arguments;
    while (curr)
    {
        if (curr->type & NODE_WORD && ft_strchr(curr->argument, '$'))
			ft_envsubst(curr->argument, environ);
        curr = curr->next;
	}
}
