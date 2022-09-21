# @author   clemedon (Clément Vidon)
####################################### BEG_3 ####

NAME		:= philo

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags

SRC_DIR     := src
OBJ_DIR     := obj
SRCS		:= \
	main.c       \
	checkargs.c  \
	init.c       \
	simulator.c  \
	simulation.c \
	time_utils.c \
	sim_utils.c  \
	utils.c
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I include
LDLIBS      := -lpthread

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKE      quietly make
# DIR_DUP   duplicate directory tree
# VALGRIND  valgrind command
# HELGRIND  helgrind command

RM          := rm -f
MAKE        := $(MAKE) --no-print-directory
DIR_DUP     = mkdir -p $(@D)
VALGRIND    := valgrind -q --leak-check=yes --show-leak-kinds=all
HELGRIND    := valgrind -q --tool=helgrind
CLS         := \r\033[K

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   linking .o -> binary
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $@)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

norm:
	norminette | grep -v "OK" || true

update:
	git stash
	git pull
	git submodule update --init
	git stash pop

sana: CFLAGS    += -O0 -g3 -fsanitize=address,undefined,integer -fno-optimize-sibling-calls
sana: LDFLAGS   += -g3 -fsanitize=address,undefined,integer
sana: all

sant: CFLAGS    += -O0 -g3 -fsanitize=thread,undefined,integer -fno-optimize-sibling-calls
sant: LDFLAGS   += -g3 -fsanitize=thread,undefined,integer
sant: all

ansi: CFLAGS    += -W -pedantic -std=c89
ansi: all

every: CFLAGS   += -Weverything
every: all

runv: $(NAME)
	$(if $(p), -$(VALGRIND) ./$(NAME) $(p), \
		echo "$(CLS)Usage: make runv p=\"<params>\"")

runh: $(NAME)
	$(if $(p), -$(HELGRIND) ./$(NAME) $(p), \
		echo "$(CLS)Usage: make runh p=\"<params>\"")

run: $(NAME)
	$(if $(p), -./$(NAME) $(p), \
		echo "$(CLS)Usage: make run p=\"<params>\"")

test_eval: $(NAME)
	-bash test/eval.sh

test_custom: $(NAME)
	$(if $(p), -bash test/custom.sh $(p), \
		echo "$(CLS)Usage: make runh p=\"<params>\"")

malloc_test: $(OBJS)
	clang -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) \
		-Ltest/ft_mallocator -lmallocator

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: runv runh run test_eval test_custom malloc_test
.SILENT:

####################################### END_3 ####
