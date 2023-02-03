/**
 * @file signal.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief シグナルハンドリングの設定
 * @version 0.1
 * @date 2023-01-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <terminal.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/ioctl.h>

void	ignore_sighandler(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	reset_ignore_signal(void)
{
	struct sigaction sa;

	sa = (struct sigaction){};
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
}

/**
* @file ignore_signal.c
* @brief SIGINT, SIGQUITのシグナルを無効化する
* @author tmuramat
* @date 2022.12.30
*/
void set_ignore_signal(void)
{
	struct sigaction sa;

	sa = (struct sigaction){};
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ignore_sighandler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
}
