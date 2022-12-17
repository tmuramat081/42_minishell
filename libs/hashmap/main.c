#include "ft_hashmap.h"

int	func()

int main (void)
{
	t_hashmap *m;
	int value_1 = 41;
	int value_2 = 23;
	int value_3 = 34;

	void *arg;

	m = ft_hashmap_init(NULL);
	ft_hashmap_insert(m, "USER1", &value_1);
	ft_hashmap_insert(m, "USER2", &value_2);
	ft_hashmap_insert(m, "USER3", &value_3);
	ft_hashmap_find(m, "USER1", &arg);
	ft_hashmnp_iterate(m, func, NULL);
	printf("%d\n", *((int *)arg));
	ft_hashmap_delete(&m);
	return (0);
}