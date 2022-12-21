#include "ft_hashmap.h"
#include "minishell.h"
void	unset(char **arg, t_hashmap *map)
{
	size_t i;

	i = 0;
	while (arg[i])
	{
		ft_hashmap_remove(map, arg[i]);
		i++;
	}
}
