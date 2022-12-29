#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

void	builtin_unset(char **args, t_shell	*msh);
void	builtin_export(char **args, t_shell	*msh);
void	builtin_env(char **args, t_shell *msh);
int		builtin_echo(char **args, t_shell *msh);
void	builtin_exit(char **args, t_shell *msh);

#endif