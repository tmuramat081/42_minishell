/*
#include <libc.h>
int main(void)
{
	char filename[80];
	char str[512];
	char *ptr;
	FILE *fp;

	sprintf(filename, "/tmp/ls%d.tmp", getpid());
	sprintf(str, "pwd  > %s", filename);
	system(str);
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("error!!!\n", stderr);
		exit (-1);
	}
	while (1)
	{
		fgets(str, 512, fp);
		if (feof(fp))
		{
			break ;
		}
		ptr = strchr(str, '\n');
		if (ptr != NULL)
		{
			*ptr = '\0';
		}
		printf("%s\n", str);
	}
	close((int)fp);
	printf(str, "rm -f %s", filename);
	return (0);
}
*/
#include <libc.h>
int execve()
{
	char *args[] = {
		"/bin/echo",
		"abc",
		"def",
		NULL 
	};

	execve(args[0], args, NULL);
	//printf("pwd  > %s", args);

	//制御が戻ってくるのは、エラーが発生した場合のみ
	perror(args[0]);
	return -1;
}