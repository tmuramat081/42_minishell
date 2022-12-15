#include "minishell.h"

/** コマンド入力を待機 */
void	boot_minishell(char **envp)
{
	char	*line;

	(void)envp;
	line = NULL;
	while (42)
	{
		line = readline("> ");
		add_history(line);
		lexer_line(line);
		free(line);
	}
}

/**
 * @brief 起動時バナーの表示（仮）
 *
 */
void	put_banner(void)
{
	ft_putendl_fd("DEVELOPMENT TEST", 1);
}

/**
 ***************************************************************
 *	function: main
 *
 * @params[argc] コマンドライン引数の数
 * @params[argv] コマンドライン引数の配列
 * @params[envp] 環境変数へのポインタ
 ***************************************************************
*/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	put_banner();
	boot_minishell(envp);
	return (0);
}
