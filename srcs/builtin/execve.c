#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	char	command[] = "/bin/cat";
	char	*exargv[] = {"-n", NULL};
	char	*exenvp[] = {NULL};
	int		return_code;

	return_code = 0;
	if (argc == 2)
	{
		exargv[1] = argv[1];
		if (execve(command, exargv, exenvp) == -1)
		{
			printf("%sコマンドが実行できませんでした\n", command);
			perror("");
			return_code = 1;
		}
	}
	else
	{
		printf("実行時引数の数が不当です\n");
		return_code = 2;
	}
	return (return_code);
}
