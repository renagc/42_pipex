#Colors
COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

#Targets
NAME = pipex

#Compiler flags
CC = @gcc
CFLAGS = -Wall -Wextra -Werror

RM = @rm -rf

#Library directories
ARM=lib/arm/libftprintf.a \
	lib/arm/libft.a
AMD=lib/amd/libftprintf.a \
	lib/amd/libft.a

#ShellCommands
UNAME_P=$(shell uname -p)
FIND_OBJ_FOLDER=$(shell find src/ -type d -name "obj")

#Source files
SRC=src/main.c \
	src/utils.c
OBJ=$(SRC:%.c=%.o)

#Phony targets
.PHONY: all clean fclean re

all: $(NAME)
$(NAME): $(OBJ)
ifeq ($(UNAME_P),x86_64)
	$(CC) $(CFLAGS) $(SRC) $(AMD) -o pipex
else
	$(CC) $(CFLAGS) $(SRC) $(ARM) -o pipex
endif
	@echo "$(COLOUR_GREEN)Compiled$(COLOUR_END)"

sanitize:
	$(CC) $(SRC) lib/libftprintf.a -fsanitize=address -g -o pipex
	@echo "$(COLOUR_GREEN)Make Sanitize Done$(COLOUR_END)"

clean:
	$(RM) $(OBJ)
	@echo "$(COLOUR_GREEN)$(OBJ) Removed$(COLOUR_END)"

fclean: clean
	$(RM) pipex
	@echo "$(COLOUR_GREEN)$(NAME) removed$(COLOUR_END)"

run:
	make sanita && ./$(NAME) infile "grep ola" "wc -l" outfile
make re: fclean all