#ifndef LIBAST_H
# define LIBAST_H

# include <stdio.h.>
# include <stdbool.h>

struct s_value {
	void
}	t_value;

typedef s_binary_tree t_binary_tree;
struct s_binary_tree {
	t_binary_tree	*left;
	t_binary_tree	*right;
	t_value			*value;
};

typedef enum e_dtype {
  AST_DTYPE_BOOL,
  AST_DTYPE_INT,
  AST_DTYPE_LONG,
  AST_DTYPE_FLOAT,
  AST_DTYPE_DOUBLE,
  AST_DTYPE_STRING,
} t_dtype;


typedef struct s_ast{
  t_dtype dtype;
  long nvar;
  void *var;
  long *vidx;
  char *exp;
  void *ast;
  void *error;
} t_ast;



ast_t *ast_init(void);


int ast_build(ast_t *ast, const char *str, const ast_dtype_t dtype, const bool eval);
int ast_set_var(ast_t *ast, const long idx, const void *value, const size_t size, const ast_dtype_t dtype);
int ast_eval(ast_t *ast, void *value);
void ast_perror(const ast_t *ast, FILE *fp, const char *msg);
void ast_destroy(ast_t *ast);

#endif