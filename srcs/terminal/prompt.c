#include "minishell.h"
#include "constant.h"
#include "ft_snprintf.h"

/**
 * @brief プロンプト名の取得
 *
 * @return char*
 */
char	*get_prompt(void)
{
	char	*prompt;

	prompt = (char *)ft_xmalloc(sizeof(char) * PROMPT_LEN);
	ft_snprintf(prompt, PROMPT_LEN, "%s > ", PROMPT_NAME);
	return (prompt);
}
