#include "ft_hashmap.h"
#include "minishell.h"
void	unset(char *arg, t_hashmap *map)
{
	if(!arg)
		return ;
	ft_hashmap_remove(map, arg);
}
