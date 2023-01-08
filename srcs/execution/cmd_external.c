#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>


/** 
 * @brief ファイルをオープンする際のフラグを取得する。
 * 
 * @param redirect_type 
 * @return int 
 */
static int     get_open_flags(int redirect_type)
{
    int flags;

    flags = 0;
    if (redirect_type & NODE_RDIR_INPUT)
    {
        flags = O_RDONLY;
    }
    else
    {
        flags = O_RDONLY | O_CREAT | 0666;
        if (redirect_type & NODE_RDIR_OUTPUT)
            flags |= O_TRUNC;
        else
            flags |= O_APPEND;
    }
    return (flags);
}

/**
 * @brief ファイルディスクリプターの複製先を取得する。
 * 
 * @param redirect_type 
 * @return int 
 */
static int get_new_fd(int redirect_type)
{
    if (redirect_type & NODE_RDIR_INPUT)
        return (STDIN_FILENO);
    else
        return (STDOUT_FILENO);
}

/**
 * @brief リダイレクトの設定を行う。
 * @detail 新規にファイルを開き（open）、入力／出力先に指定（dup2）する。
 * @param process 
 */
void    set_redirection(t_process process)
{
    int flags;
    int old_fd;
    int new_fd;
    
    flags = get_open_flags(process.redirect_type);
    new_fd = get_new_fd(process.redirect_type);
    old_fd = open(process.redirect_file, flags);
    if (old_fd == -1)
    {
        exit(EXIT_FAILURE);
    }
    if (dup2(old_fd, new_fd) < 0)
    {
        close(old_fd);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief 外部コマンドを実行する
 *
 * @param args
 * @param msh
 */
void	exec_external_command(char **args, t_process process, t_shell *msh)
{
	pid_t	pid;
	(void)msh;
	(void)process;

	pid = fork();
	if (pid == 0)
	{
        if (process.redirect_file)
            set_redirection(process);
		ft_execvpe(args[0], args, construct_environ(msh->envs));
		perror("command not found\n");
		exit (EXIT_FAILURE);
	}
	else if (pid < 0)
		exit(EXIT_FAILURE);
	while (waitpid(pid, NULL, 0) <= 0);
	return ;
}