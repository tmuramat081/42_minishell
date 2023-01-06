#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "libast.h"
# include "ft_hashmap.h"
# include "ft_vector.h"

struct s_executer {
	int	pipe;
}	t_executer;

int		builtin_unset(char **args, t_shell *msh);
int		builtin_export(char **args, t_shell	*msh);
int		builtin_env(char **args, t_shell *msh);
int		builtin_echo(char **args, t_shell *msh);
int		builtin_exit(char **args, t_shell *msh);
int		builtin_cd(char **args, t_shell *msh);
int		builtin_pwd(char **args, t_shell *msh);

void	execute_syntax_tree(t_ast *syntax_tree, t_shell *msh);
void	execute_builtin_command(char **args, t_shell *msh);

char	**construct_environ(t_hashmap *map);
int		ft_execvpe(const char *file, char *const argv[], char *const envp[]);
char	**convert_vector_to_array(t_vector *src);

#endif