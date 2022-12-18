#include "minishell.h"
#include "lexer.h"

#define INIT_SIZE 36

/**
 * @brief 3つの読み取り状態を遷移させる
 *
 * @param c
 * @param cur_state
 */
void	handle_state(char c, t_state *cur_state)
{
	if (c == '\0')
	{
		*cur_state == STATE_NORMAL;
		return ;
	}
	if (*cur_state == STATE_NORMAL)
	{
		if (c == '\'')
			*cur_state = STATE_SINGLE_QUOTE;
		else if (c == '\"')
			*cur_state = STATE_DOUBLE_QUOTE;
	}
	else if ((*cur_state == STATE_DOUBLE_QUOTE && (c == '"'))
		|| (*cur_state == STATE_SINGLE_QUOTE && c == '\''))
		*cur_state = STATE_NORMAL;
}

void	check_token(char c)
{
	printf("%c", c);
	return ;
}

bool	is_separator(char c)
{

}

/**
 * @brief 文字列を走査し、トークンを見つけたら切り出して動的配列に格納する
 *
 * @param str 切り出した文字を格納するバッファ
 * @param line 走査する文字列
 * @return
 */
void	scan_line(t_vector *str, char *line)
{
	static t_state	cur_state = STATE_NORMAL;
	char			*top;
	size_t			i;

	top = line;
	i = 0;
	while (true)
	{
		handle_state(line[i], &cur_state);
		if (cur_state == STATE_NORMAL)
		{
			check_token(line[i]);
			line[i] = '\0';
			ft_vector_push_back(str, strdup(top));
			top = &line[i+1];
			if (line[i] == '\0')
				break ;
		}
		i++;
	}
	cur_state = STATE_NORMAL;
}

/**
 * @brief デバッグ出力
 *
 * @param data
 */
void print_chunk(void	*data)
{
	char *chunk = data;
	printf("%s\n", chunk);
}

/**
 * @brief 入力された文字列を解析（字句解析）する
 *
 * @param line 入力された文字列
 */
void	lexer_line(char *line)
{
	t_vector	*str;
	t_deque *token;

	str = ft_vector_init(sizeof(char *), INIT_SIZE);
	token = ft_deque_init(sizeof(t_token), INIT_SIZE);
	scan_line(str, line);
	ft_vector_foreach(str, print_chunk);
	//token = tokenizer(str);
}
