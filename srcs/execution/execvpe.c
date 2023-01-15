/**
 * @file execvpe.c
 * @author tmuramat (tmuramat@student.42tokyo.jp)
 * @brief execvpeの再実装。環境変数PATHを参照し、該当のプログラムをコマンドとして実行する。
 * @version 0.1
 * @date 2023-01-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "execution.h"
#include "minishell.h"
#include "ft_snprintf.h"
#include "ft_hashmap.h"
#include "ft_printf.h"

/**
 * @brief 環境変数テーブルからPATHの値を取得する。
 *
 * @param envp
 * @return char*
 */
char 	*get_environ_value(char *const envp[], char *key)
{
	size_t	i;
	size_t	key_len;

	if (!envp || !*envp)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
			return (&envp[i][key_len]);
		i++;
	}
	return (NULL);
}

/**
 * @brief 実行可能なエラーかどうかを判定する。
 * @details EACEESS:アクセス権限がない, ENOENT:パスが存在しない, ESTALE:ファイルハンドルが古い, ENOTDIR: ディレクトリではない, ENODEV: デバイスが存在しない, ETIMEDOUT: 操作がタイムアウトした
 * @return true　上記のエラーである場合
 * @return false 上記以外のエラーである場合
 */
static bool is_expected_error()
{
	if (errno == EACCES || errno == ENOENT
		|| errno == ESTALE || errno == ENOTDIR
		|| errno == ENODEV || errno == ETIMEDOUT)
		return (true);
	return (false);
}

/**
 * @brief 各PATHとファイル名を組み合わせてFull PATHを作成し、execveを実行する
 *
 * @param paths
 * @param file
 * @param argv
 * @param envp
 */
void	try_executable_path(char **paths, const char *file, char *const argv[], char *const envp[])
{
	size_t	i;
	char	*buffer;
	size_t	path_len;
	size_t	file_len;

	file_len = ft_strlen(file);
	i = 0;
	while (paths[i])
	{
		path_len = ft_strlen(paths[i]);
		buffer = (char *)ft_xmalloc(sizeof(char) * (file_len + path_len + 1 + 1));
		ft_snprintf(buffer, file_len + path_len + 1 + 1, "%s/%s", paths[i], file);
		execve(buffer, argv, envp);
		if (!is_expected_error())
			return ;
		free(buffer);
		i++;
	}
}

/**
 * @brief execvpeの実装
 * @details ※GNU標準関数ではない（v - 引数配列渡し, p - PATH自動参照, e - 環境変数指定）。また、fileに'/'が含まれる場合はPATHを参照しない。
 * @param file  コマンド名
 * @param argv　起動引数
 * @param envp　環境変数
 * @return int 成功した場合は返らない。失敗した場合は-1を返し、該当のerrnoを設定する。
 */
int	ft_execvpe(const char *file, char *const argv[], char *const envp[])
{
	char	*raw_path;
	char	**paths;

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
	raw_path = get_environ_value(envp, "PATH=");
	if (!raw_path)
		return (-1);
	paths = ft_split(raw_path, ':');
	try_executable_path(paths, file, argv, envp);
	return (-1);
}