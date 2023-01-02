/**
 * @file utils.c
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

int	set_env(t_hashmap_data *map_data, void *p_envs)
{
	t_vector	*envs;
	t_env		*env;

	env = (t_env *)malloc(sizeof(t_env));
	envs = (t_vector *)p_envs;
	env->key = map_data->key;
	env->value = map_data->value;
	ft_vector_push_back(envs, env);
	return(1);
}


char	**convert_vector_to_array(t_vector *src)
{
	char	**arr;
	size_t	len;
	t_env	env;
	size_t	i;

	arr = (char **)ft_xmalloc(sizeof(char *) * (ft_vector_size(src) + 1));
	i = 0;
	while (!ft_vector_is_empty(src))
	{
		ft_vector_pop_back(src, &env);
		len = ft_strlen(env.key) + ft_strlen(env.value) + 1 + 1;
		arr[i] = (char *)ft_xmalloc(sizeof(char) * len);
		ft_snprintf(arr[i], len, "%s=%s", env.key, env.value);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**construct_environ(t_hashmap *envs)
{
	t_vector	*tmp_envs;
	char		**envp;

	tmp_envs = ft_vector_init(sizeof(t_env), 32);
	ft_hashmap_iterate(envs, set_env, tmp_envs);
	envp = convert_vector_to_array(tmp_envs);
	ft_vector_delete(&tmp_envs);
	return (envp);
}


/**
 * @brief 環境変数テーブルからPATHの値を取得する
 *
 * @param envp
 * @return char*
 */
char 	*get_environ_value(char *const envp[], char *key)
{
	size_t	i;
	size_t	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
			return (&envp[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

/**
 * @brief 実行可能なエラーかどうかを判定する
 *
 * @return true
 * @return false
 */
bool is_expected_error()
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
		buffer = (char *)malloc(sizeof(char) * (file_len + path_len + 1 + 1));
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
 * @detail ※GNU標準関数ではない（v - 引数配列渡し, p - PATH自動参照, e - 環境変数指定）。また、fileに'/'が含まれる場合はPATHを参照しない。
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
	raw_path = get_environ_value(envp, "PATH");
	paths = ft_split(raw_path, ':');
	try_executable_path(paths, file, argv, envp);
	return (-1);
}