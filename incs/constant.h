#ifndef CONSTANT_H
# define CONSTANT_H

/** Error messages */
# define MSG_NO_FILE_DIR "No such file or directory"
# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_NOT_VALID_ID "not a valid identifier"
# define MSG_TOO_MANY_ARGS "too many arguments"
# define MSG_NUM_ARG_REQUIRED "numeric argument required"
/** Escape sequences */
# define DEFAULT "\033[0;0m"
# define BOLD "\033[1m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"
# define WHITE "\033[0;97m"
# define DEL "\033[2K"
# define MOVE "\033[1F"
# define CR "\033[1G"

/** Prompt */
# define PROMPT_NAME "m-shell"
# define HEREDOC_PROMPT "> "
# define PROMPT_LEN 64
# define BANNER "\n\
.##.....##..........######..##.....##.########.##.......##......\n\
.###...###.........##....##.##.....##.##.......##.......##......\n\
.####.####.........##.......##.....##.##.......##.......##......\n\
.##.###.##.#######..######..#########.######...##.......##......\n\
.##.....##...............##.##.....##.##.......##.......##......\n\
.##.....##.........##....##.##.....##.##.......##.......##......\n\
.##.....##..........######..##.....##.########.########.########\n\
"
# define BANNER_DEV "<.......... DEBUG MODE ..........>"

#endif