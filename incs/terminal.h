#ifndef TERMINAL_H
# define TERMINAL_H

# ifdef DEBUG
#  define DEBUG 1
# else
#  define DEBUG 0
# endif

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
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
	int			exit_status;
}	t_shell;

/************* terinal ***************/
t_shell		*init_minishell(void);
void		boot_minishell(t_shell *msh);

/******* Environent variables ********/
t_hashmap	*init_environ(void);
t_env		parse_environ(const char *str);
void		sort_environs(t_env *env);
char		*ft_getenv(const char *key, t_hashmap *envs);
int			ft_setenv(t_env *env, t_hashmap *envs, int overwrite);


/*************  Prompt ***************/
char		*get_prompt(void);
void		put_banner(void);

/*************  Signal ***********/
void		ignore_signal(void);
void		handle_error(char *message, char *command);

//********** debug command ********/
void		boot_minishell_dev(t_shell *msh);
void		print_tokens(t_vector *tokens);
void		print_nodes(t_ast_node *node);
void		print_commands(t_ast_node *node);
void		print_output(void);
void		print_input(char *line);
char		*get_node_type(t_node_type	type);

#endif
