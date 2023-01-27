#ifndef EXPANSION_H
# define EXPANSION_H

#include "libast.h"
#include "terminal.h"

void    expand(t_ast_node *syntax_tree, t_shell *msh);
void    expand_environs(t_command *command, t_hashmap *environ);
int     ft_wordexp_env(char *words, char **buff, t_hashmap *environ);
char    *w_newword (size_t *act_len, size_t *max_len);
char    *w_addstr(char *buff, size_t *act_len, size_t *max_len, const char *str);
char    *w_addchar(char *buff, size_t *act_len, size_t *max_len, char ch);

#endif