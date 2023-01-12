#ifndef LIBAST_H
# define LIBAST_H

#include <stdio.h>

typedef struct s_ast_node t_ast_node;
typedef struct s_ast t_ast;
typedef	enum e_node_type t_node_type;
typedef struct s_data t_data;
typedef struct s_redirect t_redirect;
typedef struct s_command t_command;
typedef struct s_arg t_arg;

enum e_node_type {
	NODE_PIPELINE		= (1 << 0),
	NODE_SEQUENCE 		= (1 << 1),
	NODE_RDIR_INPUT 	= (1 << 2),
	NODE_RDIR_APPEND 	= (1 << 3),
	NODE_RDIR_OUTPUT 	= (1 << 4),
	NODE_RDIR_HEREDOC 	= (1 << 5),
	NODE_COMMAND		= (1 << 6),
	NODE_ARGUMENT		= (1 << 7),
	NODE_FILENAME 		= (1 << 8),
	NODE_ALL			= ~0
};

struct s_arg
{
	char	*arg;
	t_arg	*next;
};

struct s_redirect
{
	t_node_type 	dir;
	int				fd;
	char			*file;
	t_redirect		*next;
};

struct s_command
{
	t_arg		*args;
	t_redirect	*redirects;
};

struct s_ast_node
{
	int			type;
	t_ast_node	*left;
	t_ast_node	*right;
	t_command	*command;
};

struct s_ast
{
	t_ast_node	*root;
	size_t		len;
	int			error;
};

t_ast		*ast_init(void);
t_ast_node	*ast_node_create (void);
t_ast_node	*ast_parent_create (t_ast_node* left, t_ast_node* right);
void		ast_node_delete (t_ast_node* node );
void		ast_node_set_type (t_ast_node* node , t_node_type node_type);
void		ast_node_set_data (t_ast_node* node , char * data);
void		ast_node_set(t_ast_node *node, t_node_type type, char *data);
void		ast_delete(t_ast **ast);
size_t		ast_count_nodes(t_ast_node *root);

#endif
