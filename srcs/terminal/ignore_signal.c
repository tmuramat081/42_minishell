#include <libc.h>

void ignore_signal(void)
{
	// ignore "Ctrl-C" キーボードからの割り込みシグナル
	signal(SIGINT, SIG_IGN);
	// ignore "Ctrl-Z" 端末からの一時停止シグナル
    signal(SIGTSTP, SIG_IGN);
	// ignore "Ctrl-\" キーボードによる中止シグナル
    signal(SIGQUIT, SIG_IGN);
}
