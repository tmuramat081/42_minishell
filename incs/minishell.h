#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef DEBUG
#  define DEBUG 1
# else
#  define DEBUG 0
# endif

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "constant.h"
# include "ft_hashmap.h"
# include "ft_vector.h"
# include "libast.h"
# include "lexer.h"

typedef struct s_env {
	char	*key;
	char	*value;
}	t_env;

typedef struct s_shell {
	t_hashmap	*envs;
	char		*prompt;
}	t_shell;

/************* terinal ***************/
t_shell		*init_minishell(void);
t_hashmap	*init_environ(void);
char		*get_prompt(void);
void		boot_minishell(t_shell *msh);
void		put_bunner(void);
void		sort_environs(t_env *env);
void		ignore_signal(void);

//********** debug command ********/
void		print_tokens(t_vector *tokens);
void		print_nodes(t_ast *ast);
void		print_output(void);
void		print_input(char *line);

#endif
