//プログラムを実行するとプロセスが生成され、生成されたプロセスは1つの入力ポート、2つの出力ポートを持つ。
//入力ポートは「標準入力」、出力ポートは「標準出力」と「標準エラー出力」と呼ばれる。
//通常は標準入力にキーボードから入力をし、標準出力を通じて画面に実行結果が出力される。
//エラーがある場合には標準エラー出力を通じて出力され、それぞれのポートは上記左から順に0,1,2と番号が付いている。
//「ls | wc」を実行したい場合、イメージとしては「ls」の標準出力先を「wc」の標準入力につなげる。

//pipeを作る関数
int pipe(int pipefd[2]);

//port番号oldを複製して、port番号newに上書きする関数
int dup3(int oldfd, int newfd);

//port番号fdを閉じる関数
int close(int fd);

//fileにあるコマンドを実行する関数
int execvp(const char *file, char *const argv[]);

//子プロセスを作る関数
//pid_t fork(void);
int fork(void);

//親プロセスが子プロセスの終了を待つ関数
//これをしないと、ゾンビプロセス発生の恐れがある
//pid_t wait(int *status);
int wait(int *status);

//execvpはNULLがあるところを引数リストの終点とみるため、"|"のあるところをNULLにする
//"ls", "NULL", "head", "NULL", "wc"と、コマンドを3つに分けられる
//つまり、argvから見ると"ls", argv + 2から見ると"head"というコマンドになる
//pipe_countはパイプの数を、pipe_locate[10]にはパイプの場所を記録する
//0個目のパイプがargv[-1]のところにあると考え、pipe_locate[0]を-1に初期化する
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int main(void)
{
	char *argv[] = {"ls", "|", "head", "|", "wc", NULL};
	int	i;
	int	pipe_locate[10];
	int	pipe_count;
	int	status;

	pipe_count = 0;
	pipe_locate[0] = -1;
	i = 0;
	while (argv[i] != NULL)
	{
		if (strcmp(argv[i], "|") == 0)
		{
			pipe_count++;
			pipe_locate[pipe_count] = i;
			argv[i] = NULL;
		}
		i++;
	}
	//pfd[9][2]はパイプを格納するための変数
	int	pfd[9][2];
	//もしパイプが一切なかった場合の処理が以下で、fork()で子プロセスを作り、そこでコマンドを実行
	if (pipe_count == 0)
	{
		if (fork() == 0)
		{
			execvp(argv[0], argv);
			exit (0);
		}
		//以下は親プロセスで、子プロセス終了を待っている
		else
		{
			wait(&status);
		}
	}
	i = 0;
	while (i < pipe_count + 1 && pipe_count != 0)
	{
		if (i != pipe_count)
		{
			//最後のコマンドでない限り、pipeを作成
			pipe(pfd[i]);
		}
		if (fork() == 0)
		{
			//子プロセス
			if (i == 0)
			{
				//最初のコマンドなので標準出力をパイプの入口へ繋ぐ
				dup2(pfd[i][1], 1);
				close(pfd[i][0]);
				close(pfd[i][1]);
			}
			else if (i == pipe_count)
			{
				//最後のコマンドなので標準入力をパイプの出口へ繋ぐ
				dup2(pfd[i - 1][0], 0);
				close(pfd[i - 1][0]);
				close(pfd[i - 1][1]);
			}
			else
			{
				//途中のコマンドなので上記の処理両方をする
				dup2(pfd[i - 1][0], 0);
				dup2(pfd[i][1], 1);
				close(pfd[i - 1][0]);
				close(pfd[i - 1][1]);
				close(pfd[i][0]);
				close(pfd[i][1]);
			}
			execvp(argv[pipe_locate[i] + 1], argv + pipe_locate[i] + 1);
			exit (0);
		}
		else if (i > 0)
		{
			//親プロセス
			//繋げ終わったパイプを閉じる
			close(pfd[i - 1][0]);
			close(pfd[i - 1][1]);
		}
		i++;
	}
	//以下が多段パイプの肝となり、コマンドはパイプ数+1個なのでpipe_count+1回ループを回す
	//
	i = 0;
	while (i < pipe_count + 1)
	{
		wait(&status);
		i++;
	}
	return (0);
}