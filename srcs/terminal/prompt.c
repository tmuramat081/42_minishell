/**
 * @file prompt.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief プロンプトの生成
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "terminal.h"
#include "constant.h"
#include "ft_printf.h"
#include "ft_snprintf.h"

/**
 * @brief 起動時バナーの表示
 *
 */
void	put_banner(void)
{
	if (DEBUG)
		ft_printf("%s%s%s\n", RED, BANNER_DEV, DEFAULT);
	else
		ft_printf("%s\n", BANNER);
}

/**
 * @brief プロンプト名を生成する
 * @details　プロンプト名の文字列を動的に生成する。TODO: 環境変数PS1からの取得を要検討。
 * @return char*　生成した文字列
 */
char	*get_prompt(void)
{
	char	*prompt;

	prompt = (char *)ft_xmalloc(sizeof(char) * PROMPT_LEN);
	ft_snprintf(prompt, PROMPT_LEN, "%s%s > %s", GREEN, PROMPT_NAME, DEFAULT);
	return (prompt);
}
