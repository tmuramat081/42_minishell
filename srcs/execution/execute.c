#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"



void    execute_internal_command(t_ast *syntax_tree, t_shell *msh)
{
    if !(ft_strcmp("echo"))
        builtin_echo();
    else if (!ft_strcmp("env"))
        builtin_env():
    else if (!ft_strcmp("export"))
        builtin_export();
    else if (!ft_strcmp("unset"))
        builtin_unset();
    else if (!ft_strcmp("exit"))
        builtin_unseet();
}