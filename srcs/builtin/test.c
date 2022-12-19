//my_pipe.c
/*
#include <libc.h>

int main(int argc, char **argv)
{
	int fdp[2];
	long i;

	if (pipe(fdp) < 0)
	{
		perror("pipe\n");
		exit (1);
	}
	char c = 'a';
	i = 1;
	while (1)
	{
		write(fdp[1], &c, 1);
		printf("i = %ld\n", i);
		i++;
	}
	return (0);
}
*/
/*
//microshell.c
//実行は ./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo i love my microshell microshell i love my microshell
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int fd;

int err(char *string)
{
	while (*string)
		write(2, string++, 1);
	return 1;
}

int cdir(char **argv, int i)
{
	if (i != 2)
		return err("error: cd: bad arguments\n");
	if (chdir(argv[1]))
		return err("error: cd: cannot change directory to ") & err(argv[1]) & err("\n");
	return 0;
}

int ex(char **argv, char **envp, int i)
{
	int fds[2];
	int	res;
	int pip = (argv[i] && !strcmp(argv[i], "|"));
	
	if (pip && (pipe(fds)))
		return err("error: fatal\n");
	int pid = fork();
	if (!pid)
	{
		argv[i] = 0;
		if (dup2(fd, 0) == -1 | close(fd) == -1 | (pip && (dup2(fds[1], 1) == -1 | close(fds[0]) == -1 | close(fds[1]) == -1)))
			return err("error: fatal\n");
		execve(*argv, argv, envp);
		return err("error: cannot execute ") & err(*argv) & err("\n");
	}
	if ((pip && (dup2(fds[0], fd) == -1 | close(fds[0]) == -1 | close(fds[1]) == -1)) | (!pip && dup2(0, fd) == -1) | waitpid(pid, &res, 0) == -1)
		return err("error: fatal\n");
	return WIFEXITED(res) && WEXITSTATUS(res);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	int i = 0;
	int j = 0;

	fd = dup(0);
	
	while (argv[i] && argv[++i])
	{
		argv = argv + i;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (!strcmp(*argv, "cd"))
			j = cdir(argv, i);
		else if (i)
			j = ex(argv, envp, i);
	}
	return ((dup2(0, fd) == -1) && err("error: fatal\n")) | j;
}
*/
/*
#include <libc.h>
char *substr(const char *src, int m, int n)
{
	int len = n - m;
	char *dest = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = m; i < n && (*(src + i) != '\0'); i++)
	{
		*dest = *(src + i);
		dest++;
	}
	*dest = '\0';
	return (dest - len);
}

int main(void)
{
	char src[] = "substr function Implementation";
	int m = 7;
	int n = 12;
	char *dest = substr(src, m, n);
	printf("%s\n", dest);
	return (0);
}
*/
/*
#include <libc.h>

char *substr(const char *src, int m, int n)
{
	int len = n - m;
	char *dest = (char *)malloc(sizeof(char) * (len + 1));
	strncpy(dest, (src + m), len);
	return (dest);
}

int main(void)
{
	char src[] = "substr function Implementation";
	int m = 7;
	int n = 12;
	char *dest = substr(src, m, n);
	printf("%s\n", dest);
	return (0);
}
*/
#include <stdio.h>
 
// Naive method to find a pair in an array with a given sum
void findPair(int nums[], int n, int target)
{
    // consider each element except the last
    for (int i = 0; i < n - 1; i++)
    {
        // start from the i'th element until the last element
        for (int j = i + 1; j < n; j++)
        {
            // if the desired sum is found, print it
            if (nums[i] + nums[j] == target)
            {
                printf("Pair found (%d, %d)\n", nums[i], nums[j]);
                return;
            }
        }
    }
 
    // we reach here if the pair is not found
    printf("Pair not found");
}
 
int main(void)
{
    int nums[] = { 8, 7, 2, 5, 3, 1 };
    int target = 10;
 
    int n = sizeof(nums)/sizeof(nums[0]);
 
    findPair(nums, n, target);
 
    return 0;
}
