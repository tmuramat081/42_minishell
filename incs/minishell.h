#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_deque.h"
# include "ft_vector.h"

typedef enum e_value_type {
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
}	t_value_type;

struct s_token {
	char			*value;
	t_value_type	type;
}	t_token;

void	lexer_line(char *line);

#endif