#include "expansion.h"
#include "ft_vector.h"
#include "ft_hashmap.h"
#include "terminal.h"
#include "libast.h"

char    *search_environment(char *key, t_hashmap *environ)
{
    char    *value;

    if (!ft_hashmap_find(environ, key, (void **)&value))
        return (ft_calloc(1, sizeof(char)));
    return (value);
}

void wordexp_env(char **word, t_hashmap *environ)
{
    char *expanded;

    char *pt = strchr(*word, '$');
    if (!pt)
        return ;
    *pt = '\0';
    pt += 1;
    expanded = search_environment(pt, environ);
    if (expanded)
        *word = ft_strjoin(*word, expanded);
}

void    expand_environs(t_command *command, t_hashmap *environ)
{
    t_argument *curr;

    curr = command->arguments;
    while (curr)
    {
        if (curr->type & NODE_WORD)
            wordexp_env(&curr->argument, environ);
        curr = curr->next;
    }
}



void    expand_node(t_ast_node *node, t_shell *msh)
{
    if (!node)
        return ;
    if (node->type & NODE_COMMAND)
    {
        expand_environs(node->command, msh->envs);
    }
    expand_node(node->left, msh);
    expand_node(node->right, msh);
}

void    expand(t_ast_node *syntax_tree, t_shell *msh)
{
    expand_node(syntax_tree, msh);
}