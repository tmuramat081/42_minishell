#include "minishell.h"

#define INIT_SIZE 36

/** 文字列を
 * @brief
 *
 * @param line
 * @return t_deque
 */
void	scan_line(t_deque *str, char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		ft_deque_push_back(str, line);
		i++;
	}
}

/**
 * @brief 入力された文字列を解析（字句解析）する
 *
 * @param line 入力された文字列
 */
void	lexer_line(char *line)
{
	t_deque	*str;
	t_deque *token;

	str = ft_deque_init(sizeof(char *), INIT_SIZE);
	token = ft_deque_init(sizeof(t_token), INIT_SIZE);
	scan_line(str, line);
	//token = tokenizer(str);
}
