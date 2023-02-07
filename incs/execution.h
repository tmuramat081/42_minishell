#ifndef EXECUTION_H
# define EXECUTION_H

# include "terminal.h"
# include "libast.h"
# include "ft_hashmap.h"
# include "ft_vector.h"

# define PIPE_STDIN (1 << 0)
# define PIPE_STDOUT (1 << 1)

typedef int (*t_builtin_fn)(char **, t_shell *);

typedef struct s_builtin {
	char 			*symbol;
	t_builtin_fn	func;
}	t_builtin;

typedef struct s_pipe {
	int reader;
	int	writer;
	int in_fd;
	int state;
	int	backup[2];
}	t_pipe;

typedef struct s_process {
	char		**argv;
	t_redirect	*redirects;
	bool		is_solo;
}	t_process;

/********* Builtin commands **********/
int		builtin_unset(char **argv, t_shell *msh);
int		builtin_export(char **argv, t_shell	*msh);
int		builtin_env(char **argv, t_shell *msh);
int		builtin_echo(char **argv, t_shell *msh);
int		builtin_exit(char **argv, t_shell *msh);
int		builtin_cd(char **argv, t_shell *msh);
int		builtin_pwd(char **argv, t_shell *msh);

void	executor(t_ast_node *syntax_tree, t_shell *msh);
void	exec_command_line(t_ast_node *node, t_process process, t_shell *msh);
void	exec_pipeline(t_ast_node *node, t_process process, t_shell *msh);
void	exec_simple_cmd(t_ast_node *node, t_process process, t_shell *msh, t_pipe pipe);
void	exec_internal_command(t_builtin_fn builtin_cmd, t_process process, t_shell *msh);
void	exec_external_command(t_process process, t_shell *msh);

t_builtin_fn	search_builtin(t_process *process);
char	**construct_environ(t_hashmap *map);
int		ft_execvpe(const char *file, char *const argv[], char *const envp[]);
char	**convert_vector_to_array(t_vector *src);

/**********  Redirect **********/
int		set_redirection(t_process process);
void	reset_redirection(t_process process);
void	close_file(int fd);

/**********  Process **********/
pid_t	create_child_process(void);
void	wait_all_child_processes(size_t cnt);
void	wait_child_process(pid_t pid);

/********** Pipeline **********/
t_pipe	pipe_init(void);
void	pipe_update(t_pipe *piped);
void	pipe_fd_backup(t_pipe *pipe);
void	pipe_fd_restore(t_pipe pipe);
void	set_pipeline(t_pipe pipe);

#endif