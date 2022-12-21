#include "ft_hashmap.h"
#include <stdio.h>

int	func(t_hashmap_data *mapdata, void *data)
{
	(void)data;
	printf("%s : %d\n", mapdata->key, *(int *)mapdata->value);
	return (1);
}

int main (void)
{
	t_hashmap *m;
	int value_1 = 41;
	int value_2 = 23;
	int value_3 = 34;

	m = ft_hashmap_init(NULL);
	ft_hashmap_insert(m, "USER1", &value_1);
	ft_hashmap_insert(m, "USER2", &value_2);
	ft_hashmap_insert(m, "USER3", &value_3);
	ft_hashmap_remove(m, "USER1");
	ft_hashmap_iterate(m, func, NULL);
	return (0);
}