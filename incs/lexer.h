#ifndef LEXER_H
# define LEXER_H

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

typedef void		transition_func_t(void *data);
typedef t_state		state_func_t(void *data);

t_tokenizer	*init_tokenizer(char *line);
void		delete_tokenizer(t_tokenizer *tokenizer);
bool		is_equal_character(void *ch, void *event);

#endif