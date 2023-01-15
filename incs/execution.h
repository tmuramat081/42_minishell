#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "libast.h"
# include "ft_hashmap.h"
# include "ft_vector.h"

typedef int (*t_builtin_fn)(char **, t_shell *);

typedef struct s_builtin {
	char 			*symbol;
	t_builtin_fn	func;
}	t_builtin;

typedef struct s_process {
	char		**argv;
	t_redirect	*redirects;
	int			fd_backup[3];
	int			pipe[2];
	int			writer;
	int			reader;
}	t_process;


/********* Builtin commands **********/
int		builtin_unset(char **argv, t_shell *msh);
int		builtin_export(char **argv, t_shell	*msh);
int		builtin_env(char **argv, t_shell *msh);
int		builtin_echo(char **argv, t_shell *msh);
int		builtin_exit(char **argv, t_shell *msh);
int		builtin_cd(char **argv, t_shell *msh);
int		builtin_pwd(char **argv, t_shell *msh);

void	exec_command_line(t_ast_node *node, t_process process, t_shell *msh);
void	exec_pipeline(t_ast_node *node, t_process process, t_shell *msh);
void	exec_simple_cmd(t_ast_node *node, t_process process, t_shell *msh);

void	execute_syntax_tree(t_ast_node *syntax_tree, t_shell *msh);
int		exec_internal_command(t_process process, t_shell *msh);
void	exec_external_command(t_process process, t_shell *msh);

bool	is_builtin(char *args);
void    set_redirection(t_process *process);
void    reset_redirection(t_process process);
char	**construct_environ(t_hashmap *map);
int		ft_execvpe(const char *file, char *const argv[], char *const envp[]);
char	**convert_vector_to_array(t_vector *src);

#endif