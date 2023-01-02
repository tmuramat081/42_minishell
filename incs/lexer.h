#ifndef LEXER_H
# define LEXER_H

# define STR_RDIR ">"
# define STR_RRDIR ">>"
# define STR_LDIR "<"
# define STR_LLDIR "<<"
# define STR_SPACE " "
# define STR_PIPELINE "|"
# define STR_AMPERSAND "&"
# define STR_SEMICOLON ";"

#include <stdbool.h>
#include "ft_vector.h"

typedef enum e_state {
	STATE_NORMAL,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE,
}	t_state;

typedef struct s_tokenizer {
	char		*str;
	char		*pos;
	t_state		state;
}	t_tokenizer;


typedef enum e_token_type {
	TOKEN_NONE,
	TOKEN_STR,
	TOKEN_RDIR,
	TOKEN_RRDIR,
	TOKEN_LDIR,
	TOKEN_LLDIR,
	TOKEN_SPACE,
	TOKEN_PIPELINE,
	TOKEN_AMPERSAND,
	TOKEN_SEMICOLON,
	TOKEN_NULL,
	TOKEN_END
}	t_token_type;

typedef struct s_token {
	char			*data;
	t_token_type	type;
}	t_token;

t_vector		*lexer(char *line);
t_tokenizer		*init_tokenizer(char *line);
void			delete_tokenizer(t_tokenizer *tokenizer);
bool			is_metacharacter(char c);
bool			is_quotation(char c);
t_token_type	get_token_type(char *token_value);

#endif