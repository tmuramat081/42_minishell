#include <libc.h>

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	return (0);
}