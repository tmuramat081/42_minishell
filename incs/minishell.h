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
# include "ft_deque.h"
# include "ft_vector.h"
# include "ft_hashmap.h"

typedef struct s_env {
	char	*key;
	char	*value;
}	t_env;

typedef struct s_token {
	char	*data;
	int		type;
}	t_token;

typedef struct s_shell {
	t_hashmap	*envs;
}	t_shell;

/************* terinal ***************/
void		boot_minishell(char	**envp);
void		put_bunner(void);
t_hashmap	*init_envs(char **envp);
void		sort_environs(t_env *env);

//************* lexer ***************/
t_vector	*lexer(char *line);

//************* lexer ***************/
void		parser(t_vector *tokens, t_shell *msh);
int			parse(t_vector *tokens);

//********** builtin command ********/
void		unset(char **arg, t_hashmap *map);
void		export(char **args, t_hashmap *map);
t_env		*split_envp(char **envp);
void		env(char **args, t_hashmap *map);

//********** debug command ********/
void		print_token(void *p_str, void *p_index);
void		print_tokens(t_vector *tokens);

#endif
