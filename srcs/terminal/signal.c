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

#include <minishell.h>

/**
* @file ignore_signal.c
* @brief SIGINT, SIGTSTP, SIGQUITのシグナルを無効化する
* @author tmuramat
* @date 2022.12.30
*/

void ignore_signal(void)
{
	// ignore "Ctrl-C" キーボードからの割り込みシグナル
	signal(SIGINT, SIG_IGN);
	// ignore "Ctrl-Z" 端末からの一時停止シグナル
    signal(SIGTSTP, SIG_IGN);
	// ignore "Ctrl-\" キーボードによる中止シグナル
    signal(SIGQUIT, SIG_IGN);
}
