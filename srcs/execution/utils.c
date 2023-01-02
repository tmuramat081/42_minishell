#include "execution.h"
#include "minishell.h"

char	*ft_strchrnul(const char *s, int c)
{
	char	*cast_s;

	cast_s = (char *)s;
	while (1)
	{
		if (*cast_s == (char)c)
			return (cast_s);
		if (*cast_s == '\0')
			break ;
		cast_s++;
	}
	return (cast_s);
}
void	*ft_mempcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cast_d;
	unsigned char	*cast_s;

	if (!dst && !src)
		return (NULL);
	cast_d = (unsigned char *)dst;
	cast_s = (unsigned char *)src;
	while (n--)
		*(cast_d++) = *(cast_s++);
	return (cast_d);
}

/**
 * @brief execvpeの再実装
 * @detail （v - 引数配列渡し, p - PATH自動参照, e - 環境変数指定）。filenに'/'が含まれる場合はPATHを参照しない。
 * @param file  コマンド名
 * @param argv　起動引数
 * @param envp　環境変数
 * @return int
 */
int	ft_execvpe(const char *file, char *const argv[], char *const envp[])
{
	const char	*subp;
	size_t file_len;
	size_t path_len;

	if (!file || !*file)
	{
		errno = ENOENT;
		return (-1);
	}
	if (ft_strchr(file, '/') != NULL)
	{
		execve(file, argv, envp);
		return (-1);
	}
	const char *path = getenv("PATH");
	if (!path)
		path = "/bin:/usr/bin";
	file_len = ft_strlen(file);
  	path_len = ft_strlen(path) + 1;
	char buffer[path_len + file_len + 1];
	const char *p = path;
	while (true)
	{
		subp = ft_strchrnul(p, ':');
		char *pend = ft_mempcpy(buffer, p, subp - p);
		*pend = '/';
		ft_memcpy (pend + (p < subp), file, file_len);
		execve(buffer, argv, envp);
		if (errno || *subp++ == '\0')
			break ;
		p = subp;
	}
	return (-1);
}