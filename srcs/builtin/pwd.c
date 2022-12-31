#include "minishell.h"
/*
#include <libc.h>
#include <stdbool.h>
typedef struct s_hashmap_data {
	char	*key;
	void	*value;
	bool	in_use;
}	t_hashmap_data;

typedef struct s_hashmap {
	size_t			nbits;
	size_t			mask;
	t_hashmap_data	*data;
	size_t			len;
	size_t			cap;
	size_t 			(*hash)(const void *);
}	t_hashmap;

int pwd(char **arg, t_hashmap *map);

int main(void)
{
	char **arg;
	t_hashmap *map;
	pwd(arg, map);
	return (0);
}
*/

int pwd(char **arg, t_hashmap *map)
{
	char buf[BUFSIZ];
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	return (0);
}
