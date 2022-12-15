#include "ft_hashmap.h"

int main (void)
{
	t_hashmap *m;
	int value_1 = 1;
	int value_2 = 2;
	int value_3 = 3;

	void *arg;

	m = ft_hashmap_init(NULL);
	ft_hashmap_insert(m, "apple", &value_1);
	ft_hashmap_insert(m, "banana", &value_2);
	ft_hashmap_insert(m, "lemon", &value_3);
	ft_hashmap_get(m, "apple", &arg);
	printf("%d\n", *((int *)arg));
	return (0);
`