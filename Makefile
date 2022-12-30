# Compile variables
NAME := minishell
CC := gcc -g
CFLAGS := -Wall -Wextra -Werror
DFLAGS := -D DEBUG

SRCS_DIR := srcs/
SRCS := \
	main.c \
	terminal/environs.c \
	terminal/prompt.c \
	terminal/boot.c \
	terminal/ignore_signal.c \
	builtin/export.c \
	builtin/unset.c \
	builtin/echo.c \
	builtin/env.c \
	lexer/lexer.c \
	lexer/token.c \
	lexer/lexer_utils.c \
	parser/parser.c \
	parser/parse_separator.c \
	parser/parse_pipeline.c \
	parser/parse_redirection.c \
	parser/parse_command.c \
	parser/parse_argument.c \
	debug/print_token.c \
	debug/print_tree.c

OBJS_DIR := objs/
OBJS := ${addprefix ${OBJS_DIR},${SRCS:.c=.o}}
DEPS := ${addprefix ${OBJS_DIR},${SRCS:.c=.d}}

LIBFT_DIR := libs/ft/
LIBFT := ${LIBFT_DIR}libft.a

LIBVECTOR_DIR := libs/vector/
LIBVECTOR := ${LIBVECTOR_DIR}libvector.a

LIBDEQUE_DIR := libs/deque/
LIBDEQUE := ${LIBDEQUE_DIR}libdeque.a

LIBPQUEUE_DIR := libs/priority_queue/
LIBPQUEUE := ${LIBPQUEUE_DIR}libpqueue.a

LIBHASHSET_DIR := libs/hashset/
LIBHASHSET := ${LIBHASHSET_DIR}libhashset.a

LIBHASHMAP_DIR := libs/hashmap/
LIBHASHMAP := ${LIBHASHMAP_DIR}libhashmap.a

LIBAST_DIR := libs/ast/
LIBAST := ${LIBAST_DIR}libast.a

LIBREADLINE := -lreadline

INCS := \
	-I./incs/ \
	-I./${LIBFT_DIR}incs/ \
	-I./${LIBDEQUE_DIR}incs/ \
	-I./${LIBVECTOR_DIR}incs/ \
	-I./${LIBPQUEUE_DIR}incs/ \
	-I./${LIBHASHSET_DIR}incs/ \
	-I./${LIBHASHMAP_DIR}incs/ \
	-I./${LIBAST_DIR}incs/

# Print variab
PRINTF := printf
DEFAULT := \033[0;39m
BLUE := \033[0;94m
GREEN := \033[0;92m
RED := \033[0;91m
DEL := \033[2K
MOVE := \033[1F
CR := \033[1G

# Progress variables
SRC_TOT := ${shell expr ${words ${SRCS}} - ${shell ls -l ${OBJS_DIR} | grep .o$ | wc -l} + 1}
ifndef ${SRC_TOT}
	SRC_TOT := ${words ${SRCS}}
endif
SRC_CNT := 0
SRC_PCT = ${shell expr 100 \* ${SRC_CNT} / ${SRC_TOT}}
PROGRESS = ${eval SRC_CNT = ${shell expr ${SRC_CNT} + 1}} \
	${PRINTF} "${DEL}${GREEN}[ %d/%d (%d%%) ] ${CC} ${CFLAGS} ${DFLAGS} $< ...${DEFAULT}${CR}" \
	$(SRC_CNT) $(SRC_TOT) $(SRC_PCT)

# Main commands
${NAME}: ${LIBFT} ${LIBDEQUE} ${LIBVECTOR} ${LIBPQUEUE} ${LIBHASHSET} ${LIBHASHMAP} ${LIBAST} ${OBJS}
	@${CC} ${CFLAGS} ${DFLAGS} ${INCS} ${OBJS} ${LIBFT} ${LIBDEQUE} ${LIBVECTOR} ${LIBPQUEUE} ${LIBHASHSET} ${LIBREADLINE} ${LIBHASHMAP} ${LIBAST} -o $@
	@echo "\n${BLUE}--- ${NAME} is up to date! ---${DEFAULT}"

${LIBFT}:
	@${MAKE} -C ${LIBFT_DIR} --no-print-directory

${LIBDEQUE}:
	@${MAKE} -C ${LIBDEQUE_DIR} --no-print-directory

${LIBVECTOR}:
	@${MAKE} -C ${LIBVECTOR_DIR} --no-print-directory

${LIBPQUEUE}:
	@${MAKE} -C ${LIBPQUEUE_DIR} --no-print-directory

${LIBHASHSET}:
	@${MAKE} -C ${LIBHASHSET_DIR} --no-print-directory

${LIBHASHMAP}:
	@${MAKE} -C ${LIBHASHMAP_DIR} --no-print-directory

${LIBAST}:
	@${MAKE} -C ${LIBAST_DIR} --no-print-directory

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@${PROGRESS}
	@${CC} ${CFLAGS} ${DFLAGS} ${INCS} -c $< -o $@

-include ${DEPS}

#: Make executable file.
all: ${NAME}

#: Remove all object files.
clean:
	${RM} ${OBJS} ${DEPS}
	@${MAKE} clean -C ${LIBFT_DIR} --no-print-directory
	@${MAKE} clean -C ${LIBDEQUE_DIR} --no-print-directory
	@${MAKE} clean -C ${LIBVECTOR_DIR} --no-print-directory
	@${MAKE} clean -C ${LIBPQUEUE_DIR} --no-print-directory
	@${MAKE} clean -C ${LIBHASHSET_DIR} --no-print-directory
	@${MAKE} clean -C ${LIBHASHMAP_DIR} --no-print-directory
	@${MAKE} clean -C ${LIBAST_DIR} --no-print-directory


#: Remove all object and executable files.
fclean:	clean
	${RM} ${NAME}
	${RM} ${LIBFT}
	${RM} ${LIBDEQUE}
	${RM} ${LIBVECTOR}
	${RM} ${LIBPQUEUE}
	${RM} ${LIBHASHSET}
	${RM} ${LIBHASHMAP}
	${RM} ${LIBAST}

#: Remove and recompile all.
re: fclean
	@${MAKE} -s all

#: [debug] Print debug info.
dev: clean
	@${MAKE} ${NAME_DEV} FOR_DEBUG=1 --no-print-directory

#: Push to git repository.
git:
	git add .
	git commit
	git push origin feature

#: Display all commands.
help:
	@grep -A1 -E "^#:" --color=auto Makefile \
	| grep -v -- -- \
	| sed 'N;s/\n/###/' \
	| sed -n 's/^#: \(.*\)###\(.*\):.*/\2###\1/p' \
	| sed -e 's/^/make /' \
	| column -t -s '###'

.PHONY:
	all clean fclean re debug git help

credit:
	@echo "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "         Made with love by : \033[1;91mzjamali\033[m and \033[1;91mmbari\033[m"