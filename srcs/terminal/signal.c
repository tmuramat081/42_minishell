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
	if (sig == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	set_signal(int signal, void (*sighandler)(int))
{
	struct sigaction	sa;

	sa = (struct sigaction){};
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sighandler;
	if (sigaction(signal, &sa, NULL) < 0)
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
	set_signal(SIGINT, ignore_sighandler);
	set_signal(SIGQUIT, SIG_IGN);
	set_signal(SIGTSTP, SIG_IGN);
}
