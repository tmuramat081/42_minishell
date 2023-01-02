#include "minishell.h"
#include "constant.h"
#include "ft_printf.h"

void	print_output(void)
{
	ft_printf("%s<<<< OUTPUT >>>>%s\n", BLUE, DEFAULT);
}
