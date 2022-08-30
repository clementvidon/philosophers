# @file     Makefile
# @brief    Simple and minimalistic Makefile for C project.
# @author   clemedon (Clément Vidon)

NAME		:= philo

#------------------------------------------------#
# INGREDIENTS                                    #
#------------------------------------------------#
# CC        compilers
# CFLAGS    compiler flags
# CPPFLAGS  preprocessor flags
#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files

CC			:= clang
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -pthread -I include

SRC_DIR		:= src
OBJ_DIR		:= obj
SRCS		:= \
	main.c checkargs.c init.c \
	simulator.c simulation.c \
	time_utils.c simulator_utils.c utils.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        cleaning command
# VALGRIND  valgrind command
# HELGRIND  helgrind command
# CLS       clear the current line
# ECHO      print command and message prefix
# R         set output foreground to red
# G         set output foreground to green
# Y         set output foreground to yellow
# END       reset output foreground color

RM			:= rm -rf
VALGRIND	:= valgrind -q --leak-check=yes --show-leak-kinds=all
HELGRIND	:= valgrind -q --tool=helgrind

CLS			:= \r\033[K
MUTE		:= 1>/dev/null

#------------------------------------------------#
#	RECIPES										 #
#------------------------------------------------#
# all       build all targets
# $(NAME)   build $(NAME) target
# clean     remove objects
# fclean    remove objects and binary
# re        remove objects and binary and rebuild all

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo "$(CLS)$(NAME): created."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -n "$(CLS)Building $(NAME)..."
	@[ ! -d $(@D) ] && mkdir -p  $(@D) || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

#------------------------------------------------#
#   CUSTOM RECIPES                               #
#------------------------------------------------#
# sana          memory corruption debugging
# sant          data races debugging
# ansi          ANSI Std89 compliance
# every         explore new warnings
# update        update the repository
# norm          42 C coding style compliance
# info          standard build output
# runv          run the program with valgrind
# runh          run the program with helgrind
# malloc_test   ft_mallocator external tool rule

.PHONY: sana sant ansi every update norm info runv runh malloc_test

sana: CC		:= gcc
sana: CFLAGS	:= $(CFLAGS) -g -fsanitize=address,undefined,signed-integer-overflow
sana: $(NAME)

sant: CC		:= gcc
sant: CFLAGS	:= $(CFLAGS) -g -fsanitize=thread,undefined,signed-integer-overflow
sant: $(NAME)

ansi: CFLAGS	+= -W -Wcast-qual -Wcomma -Wconversion -Wsign-conversion -Wwrite-strings -pedantic -std=c89
ansi: all

every: CFLAGS	+= -Weverything
every: all

update:
	@git pull
	@git submodule update --init

norm:
	@norminette | grep -v "OK" || true

info: fclean
	@make --dry-run | grep -v "echo.*\".*\"\|\[.*\]"

runv: $(NAME)
	$(if $(p), @$(VALGRIND) ./$(NAME) $(p) || true, \
		@echo "$(CLS)Usage: make runv p=\"<params>\"")

runh: $(NAME)
	$(if $(p), @$(HELGRIND) ./$(NAME) $(p) || true, \
		@echo "$(CLS)Usage: make runh p=\"<params>\"")

malloc_test: $(OBJS)
	@clang -Wall -Wextra -Werror -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) \
		-Ltest/ft_mallocator -lmallocator
