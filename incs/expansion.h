#ifndef EXPANSION_H
# define EXPANSION_H

#include "libast.h"
#include "terminal.h"

# define FTWRDE_SUCCESS 0
# define FTWRDE_BADCHAR 1
# define FTWRDE_BADVAL 2
# define FTWRDE_CMDSUB 3
# define FTWRDE_NOSPACE 4
# define FTWRDE_SYNTAX 5

typedef struct s_wordexp {
	size_t		act_len;
	size_t		max_len;
	t_hashmap	*envs;
}	t_wordexp;

void		expand(t_ast_node *syntax_tree, t_shell *msh);
void		expand_environs(t_command *command, t_hashmap *environ);

int			ft_wordexp(char *words, char **buff, t_hashmap *environ);
int			we_parse_dollar(char *words, char **buff, t_wordexp *wp, size_t *offset);
int			we_parse_quote(char *words, char **buff, t_wordexp *wp, size_t *offset);
int			we_parse_params(char *words, char **buff, t_wordexp *wp, size_t *offset);

t_wordexp	w_newword(t_hashmap *environs);
char		*w_addstr(char *buff, t_wordexp *wp, const char *str);
char		*w_addchar(char *buff, t_wordexp *wp, char ch);

#endif