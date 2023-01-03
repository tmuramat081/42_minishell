#include "minishell.h"
#include "constant.h"
#include "ft_printf.h"


void	print_input(char *line)
{
	ft_printf("\n%s<<<< INPUT %s\n", RED, DEFAULT);
	ft_printf("%s\n", line);
}


void	print_output(void)
{
	ft_printf("%sOUTPUT >>>>%s\n", BLUE, DEFAULT);
}
