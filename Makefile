# @author   cvidon@42
# @brief    Makefile for C programs that does not require any dependency.

INC_DIR		= include
SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= main.c 			\
			  checkargs.c 		\
			  init.c 			\
			  simulator.c 		\
			  simulation.c 		\
			  time_utils.c 		\
			  simulator_utils.c	\
			  utils.c 			\

CC			= clang
CFLAGS		= -Wall -Wextra -Werror -Wconversion -Wsign-conversion
CPPFLAGS	= -Iinclude -pthread
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
NAME		= philo

#------------------------------------------------#
#	SHELL CMDS									 #
#------------------------------------------------#

RM			= rm -rf
VALGRIND	= valgrind -q --leak-check=yes --show-leak-kinds=all
HELGRIND	= valgrind -q --tool=helgrind
AV			= $(nullstring)

#------------------------------------------------#
#	RECIPES										 #
#------------------------------------------------#

.PHONY: all san_thread san_addr clean fclean re norm update malloc_test

all: $(NAME)

san_thread: CC := gcc
san_thread: CFLAGS := $(CFLAGS) -fsanitize=thread,undefined,signed-integer-overflow
san_thread: $(NAME)

san_addr: CC := gcc
san_addr: CFLAGS := $(CFLAGS) -fsanitize=address,undefined,signed-integer-overflow
san_addr: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@$(ECHO)"$(G)created $(END)$(NAME)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@$(ECHO)"$(G)created $(END)$@"

clean:
	@[ -d $(OBJ_DIR) ] \
		&& $(RM) $(OBJ_DIR) && $(ECHO)"$(R)removed$(END) $(OBJ_DIR)/\n" || true

fclean: clean
	@[ -f $(NAME) ] \
		&& $(RM) $(NAME) && $(ECHO)"$(R)removed$(END) $(NAME)\n" || true

re : fclean all

norm:
	@norminette | grep -v "OK" || true
	@$(ECHO)"$(G)checked norm$(END)\n"

update:
	@git pull
	@git submodule update --init
	@$(ECHO)"$(G)updated$(END)\n"

malloc_test: $(OBJS)
	@clang -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) \
		-Ltest/ft_mallocator -lmallocator

run:
	@./$(NAME) $(AV) || true
valgrind_run:
	@$(VALGRIND) ./$(NAME) $(AV) || true
helgrind_run:
	@$(HELGRIND) ./$(NAME) $(AV) || true

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
