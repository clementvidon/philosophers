# Makefile for C programs that requires no dependencies.

NAME		= a.out

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -Wconversion -Wsign-conversion -g
CPPFLAGS	= -pthread
SRCS		= main.c
OBJS		:= $(SRCS:%.c=%.o)

#------------------------------------------------#
#	SHELL CMDS									 #
#------------------------------------------------#

RM			= rm -rf
VALGRIND	= valgrind -q --leak-check=yes --show-leak-kinds=all
HELGRIND	= valgrind -q --tool=helgrind
ARGS		= ${nowhere}

#------------------------------------------------#
#	RECIPES										 #
#------------------------------------------------#

.PHONY: all san_addr san_thread clean fclean re norm update malloc_test

all: $(NAME)

san_thread: CC := gcc
san_thread: CFLAGS := $(CFLAGS) -g3 -fsanitize=address,undefined,signed-integer-overflow
san_thread: $(NAME)

san_addr: CC := gcc
san_addr: CFLAGS := $(CFLAGS) -g3 -fsanitize=address,undefined,signed-integer-overflow
san_addr: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)objects"

clean:
	@[ -f $(OBJS) ] \
		&& $(RM) $(OBJS) && $(ECHO)"$(R)removed$(END) objects\n" || true

fclean: clean
	@[ -f $(NAME) ] \
		&& $(RM) $(NAME) && $(ECHO)"$(R)removed$(END) $(NAME)\n" || true

re : fclean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) sources\n"
	@norminette -R CheckDefine | grep -v "OK" || true
	@$(ECHO)"$(G)checked$(END) headers\n"

update:
	@git pull
	@git submodule update --init
	@$(ECHO)"$(G)updated$(END)\n"

malloc_test: $(OBJS)
	@clang -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ ${OBJS} -Ltest/ft_mallocator -lmallocator

run:
	@./$(NAME) $(ARGS) || true
valgrind_run:
	@$(VALGRIND) ./$(NAME) $(ARGS) || true
helgrind_run:
	@$(HELGRIND) ./$(NAME) $(ARGS) || true

#------------------------------------------------#
#	STDOUT										 #
#------------------------------------------------#

R		= $(shell tput setaf 1)
G		= $(shell tput setaf 2)
Y		= $(shell tput setaf 3)
B		= $(shell tput setaf 4)
M		= $(shell tput setaf 5)
C		= $(shell tput setaf 6)
W		= $(shell tput setaf 7)
K		= $(shell tput setaf 8)
END		= $(shell tput sgr0)
ECHO	= echo -n "\r\033[K$(NAME): "
