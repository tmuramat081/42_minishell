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
void    expand_environs(t_command *command, t_hashmap *environ)
{
    t_argument  *curr;
    char        *pwordexp;

    curr = command->arguments;
    while (curr)
    {
        if (curr->type & NODE_WORD && ft_strchr(curr->argument, '$'))
        {
			ft_wordexp_env(curr->argument, &pwordexp, environ);
            free(curr->argument);
            curr->argument = pwordexp;
        }
        curr = curr->next;
	}
}
