#include "minishell.h"
#include "execution.h"
#include "parser.h"
#include "libast.h"
#include "ft_printf.h"
#include <unistd.h>
#include <fcntl.h>

/** 
 * @brief ファイルをオープンする。
 * 
 * @param redirect_type 
 * @return int 
 */
static int     open_file(t_process *process)
{
    char        *filename;
    const int   file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 

    filename = process->redirect_file;
    if (process->redirect_type & NODE_RDIR_OUTPUT) 
        return (open(filename, O_WRONLY | O_CREAT | O_TRUNC, file_mode));
    else if (process->redirect_type & NODE_RDIR_APPEND)
        return (open(filename, O_WRONLY | O_CREAT | O_APPEND, file_mode));
    return (open(filename, O_RDONLY));
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
 * @brief リダイレクト先の設定を行う。
 * @detail 新規にファイルを開き（open）、入力／出力先に指定（dup2）する。
 * @param process 
 */
void    set_redirection(t_process *process)
{
    int old_fd;
    int new_fd;
    
	process->fd_backup = dup(STDOUT_FILENO);
    if (process->fd_backup < 0)
    {
        exit(EXIT_FAILURE);
    }
    new_fd = get_new_fd(process->redirect_type);
    old_fd = open_file(process);
    if (old_fd == -1)
    {
        printf("%d\n", errno);
        strerror(errno);
        exit(EXIT_FAILURE);
    }
    if (dup2(old_fd, new_fd) < 0)
    {
        close(old_fd);
        exit(EXIT_FAILURE);
    }
    close(old_fd);
}

void    reset_redirection(t_process *process)
{
    int old_fd;
    int new_fd;

    if (!process->fd_backup)
        return ;
    old_fd = process->fd_backup;
    new_fd = get_new_fd(process->redirect_type);
	dup2(old_fd, new_fd);
	close(old_fd);
}