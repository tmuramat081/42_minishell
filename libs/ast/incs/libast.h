#ifndef LIBAST_H
# define LIBAST_H

#define NODETYPE(a) (a & (~NODE_DATA))	// get the type of the nodes

#include <stdio.h>

typedef enum e_node_type {
	NODE_PIPE 			= (1 << 0),
	NODE_BCKGRND 		= (1 << 1),
	NODE_SEQ 			= (1 << 2),
	NODE_REDIRECT_IN 	= (1 << 3),
	NODE_REDIRECT_OUT 	= (1 << 4),
	NODE_CMDPATH		= (1 << 5),
	NODE_ARGUMENT		= (1 << 6),
	NODE_DATA 			= (1 << 7),
} t_node_type;

typedef struct s_ast_node
{
	int					type;
	char				*data;
	struct	s_ast_node	*left;
	struct	s_ast_node	*right;
} t_ast_node;

typedef struct s_ast
{
	t_ast_node	*ast;
	size_t		len;
	int			error;
}	t_ast;


void		ast_attach_binary_branch (t_ast_node* root , t_ast_node* leftNode , t_ast_node* rightNode);
void		ast_node_set_type (t_ast_node* node , t_node_type nodetype );
void		ast_node_set_data (t_ast_node* node , char * data );
void		ast_node_delete (t_ast_node* node );
t_ast		*ast_init(void);
void		*ast_delete(t_ast **ast);
t_ast_node	*ast_root(t_ast **ast);

#endif
