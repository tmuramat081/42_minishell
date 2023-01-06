#ifndef LEXER_H
# define LEXER_H

#include <stdbool.h>
#include "ft_vector.h"

typedef struct s_tokenizer t_tokenizer;
typedef void *(* t_state_fn)(t_tokenizer *);

struct s_tokenizer {
	char		*str;
	size_t		start;
	size_t		pos;
	void		*state;
	t_vector	*tokens;
};

typedef enum e_token_type {
	TOKEN_NONE = (1 << 0),
	TOKEN_STR_PLAIN = (1 << 1),
	TOKEN_STR_SQUOTE = (1 << 2),
	TOKEN_STR_DQUOTE = (1 << 3),
	TOKEN_RDIR_INPUT = (1 << 4),
	TOKEN_RDIR_APPEND = (1 << 5),
	TOKEN_RDIR_OUTPUT = (1 << 6),
	TOKEN_RDIR_HEREDOC = (1 << 7),
	TOKEN_PIPELINE = (1 << 8),
	TOKEN_AMPERSAND = (1 << 9),
	TOKEN_SEMICOLON = (1 << 10),
	TOKEN_END = (1 << 11),
	TOKEN_RDIR = TOKEN_RDIR_INPUT
			| TOKEN_RDIR_OUTPUT
			| TOKEN_RDIR_APPEND
			| TOKEN_RDIR_HEREDOC,
	TOKEN_STR_QUOTE = TOKEN_STR_SQUOTE
					| TOKEN_STR_DQUOTE,
	TOKEN_STR = TOKEN_STR_PLAIN
				| TOKEN_STR_QUOTE,
}	t_token_type;

typedef struct s_token {
	char			*data;
	t_token_type	type;
}	t_token;

void			lexer(char *line, t_vector **tokens);
t_tokenizer		*init_tokenizer(char *line);
void			delete_tokenizer(t_tokenizer *tokenizer);
void			format_token(t_token *token);
char			next(t_tokenizer *tokenizer);
void			prev(t_tokenizer *tokenizer);
void			emit(t_tokenizer *tk, t_token_type ttype);
char			peek(t_tokenizer *tokenizer);
bool			is_redirection(int c);
bool			is_delimiter(int c);
void			*lex_general(t_tokenizer *tokenizer);
void			*lex_whitespace(t_tokenizer *tokenizer);
void			*lex_quote(t_tokenizer *tokenizer);
void			*lex_string(t_tokenizer *tokenizer);
void			*lex_redirect(t_tokenizer *tokenizer);
void			*lex_delimiter(t_tokenizer *tokenizer);
void			*lex_error(t_tokenizer *tokenizer);
void			*lex_eof(t_tokenizer *tokenizer);

#endif