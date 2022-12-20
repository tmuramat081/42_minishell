#ifndef LEXER_H
# define LEXER_H

typedef enum {
	STATE_NORMAL,
	STATE_SINGLE_QUOTE,
	STATE_DOUBLE_QUOTE,
}	t_state;

typedef enum {
	DATA_NONE,
	DATA_STR,
	DATA_RDIR,
	DATA_RRDIR,
	DATA_LLDIR,
	DATA_SPACE,
	DATA_PIPE,
	DATA_SEMICOLON,
	DATA_END
} t_data_type;

typedef struct s_data {
	void		*data;
	t_data_type	data_type;
}	t_data;

typedef struct s_tokenizer {
	char 	*str;
	char 	*pos;
} 	t_tokenizer;

bool	is_equal_character(void *ch, void *event);
typedef void		transition_func_t(void *data);
typedef t_state		state_func_t(void *data);

#endif