#ifndef EXPANSION_H
# define EXPANSION_H

#include "libast.h"
#include "terminal.h"

void    expand(t_ast_node *syntax_tree, t_shell *msh);
void    expand_environs(t_command *command, t_hashmap *environ);
void	ft_envsubst(char *str, t_hashmap *environ);

#endif