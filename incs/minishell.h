#ifndef MINISHELL_H
# define MINISHELL_H

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

/************* terinal ***************/
void		boot_minishell(char	**envp);
void		put_bunner(void);
t_hashmap	*init_envs(char **envp);
void		sort_environs(t_env *env);

/************* lexer ***************/
void		tokenizer(char *line);

/********** builtin command ********/
void		unset(char **arg, t_hashmap *map);
t_env		*split_envp(char **envp);

/********** debug command ********/
void		print_token(void *void_str);

#endif
